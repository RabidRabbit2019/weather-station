/* vim: set ai et ts=4 sw=4: */
/* vim: set ai et ts=4 sw=4: */
#include "st7735.h"
#include "stm32f103x6.h"

#define DELAY 0x80

int rm_spi_xfer( uint8_t a_dr, uint8_t * a_dst );
void delay_ms( uint32_t a_ms );
extern volatile uint32_t g_milliseconds;

// based on Adafruit ST7735 library for Arduino
static const uint8_t
  init_cmds1[] = {            // Init for 7735R, part 1 (red or green tab)
    15,                       // 15 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
      150,                    //     150 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
      255,                    //     500 ms delay
    ST7735_FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
      0x01, 0x2C, 0x2D,       //     Dot inversion mode
      0x01, 0x2C, 0x2D,       //     Line inversion mode
    ST7735_INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
      0x07,                   //     No inversion
    ST7735_PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                   //     -4.6V
      0x84,                   //     AUTO mode
    ST7735_PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
      0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    ST7735_PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
      0x0A,                   //     Opamp current small
      0x00,                   //     Boost frequency
    ST7735_PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
      0x8A,                   //     BCLK/2, Opamp current small & Medium low
      0x2A,  
    ST7735_PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    ST7735_VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
      0x0E,
    ST7735_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    ST7735_MADCTL , 1      ,  // 14: Memory access control (directions), 1 arg:
      ST7735_ROTATION,        //     row addr/col addr, bottom to top refresh
    ST7735_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05 },                 //     16-bit color

  init_cmds2[] = {            // Init for 7735R, part 2 (1.44" display)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, ST7735_WIDTH - 1,             //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, ST7735_HEIGHT - 1 },           //     XEND = 127

  init_cmds3[] = {            // Init for 7735R, part 3 (red or green tab)
    4,                        //  4 commands in list:
    ST7735_GMCTRP1, 16      , //  1: Gamma Adjustments (pos. polarity), 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735_GMCTRN1, 16      , //  2: Gamma Adjustments (neg. polarity), 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST7735_NORON  ,    DELAY, //  3: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,    DELAY, //  4: Main screen turn on, no args w/delay
      100 };                  //     100 ms delay

static void ST7735_Select() {
  GPIOB->BSRR = GPIO_BSRR_BR12;
}

void ST7735_Unselect() {
  GPIOB->BSRR = GPIO_BSRR_BS12;
}

static void ST7735_Reset() {
  GPIOB->BSRR = GPIO_BSRR_BR13;
  delay_ms( 20 );
  GPIOB->BSRR = GPIO_BSRR_BS13;
  delay_ms( 150 );
}


uint8_t g_dummy = 0;

static void ST7735_spi_write_start( uint8_t * a_src, uint32_t a_size ) {
  SPI1->DR;
  DMA1->IFCR = 0xFFFFFFFF;
  
  DMA1_Channel2->CMAR = (uint32_t)&g_dummy;
  DMA1_Channel2->CNDTR = a_size;
  DMA1_Channel2->CCR = DMA_CCR_EN;
  
  DMA1_Channel3->CMAR = (uint32_t)a_src;
  DMA1_Channel3->CNDTR = a_size;
  DMA1_Channel3->CCR = DMA_CCR_DIR
                     | DMA_CCR_MINC
                     | DMA_CCR_EN
                     ;
}


static void ST7735_spi_write_end() {
  uint32_t v_from = g_milliseconds;
  while ( ((uint32_t)(g_milliseconds - v_from)) < 50u ) {
    if ( 0 != (DMA1->ISR & (DMA_ISR_TEIF2 | DMA_ISR_TEIF3 | DMA_ISR_TCIF2)) ) {
      break;
    }
  }
  
  DMA1_Channel2->CCR &= ~DMA_CCR_EN;
  DMA1_Channel3->CCR &= ~DMA_CCR_EN;
}


static void ST7735_spi_write( uint8_t * a_src, uint32_t a_size ) {
  ST7735_spi_write_start( a_src, a_size );
  ST7735_spi_write_end();
}


static void ST7735_WriteCommand(uint8_t cmd) {
  GPIOB->BSRR = GPIO_BSRR_BR14;
  ST7735_spi_write( &cmd, sizeof(cmd) );
}


static void ST7735_WriteData(uint8_t* buff, uint32_t buff_size) {
  GPIOB->BSRR = GPIO_BSRR_BS14;
  ST7735_spi_write( buff, buff_size );
}


static void ST7735_ExecuteCommandList(const uint8_t *addr) {
    uint8_t numCommands, numArgs;
    uint16_t ms;

    numCommands = *addr++;
    while(numCommands--) {
        uint8_t cmd = *addr++;
        ST7735_WriteCommand(cmd);

        numArgs = *addr++;
        // If high bit set, delay follows args
        ms = numArgs & DELAY;
        numArgs &= ~DELAY;
        if(numArgs) {
            ST7735_WriteData((uint8_t*)addr, numArgs);
            addr += numArgs;
        }

        if(ms) {
            ms = *addr++;
            if(ms == 255) {
              ms = 500;
            }
            delay_ms( ms );
        }
    }
}

static void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    // column address set
    ST7735_WriteCommand(ST7735_CASET);
    uint8_t data[4] = { 0x00, (uint8_t)(x0 + ST7735_XSTART), 0x00, (uint8_t)(x1 + ST7735_XSTART) };
    ST7735_WriteData(data, sizeof(data));

    // row address set
    ST7735_WriteCommand(ST7735_RASET);
    data[1] = y0 + ST7735_YSTART;
    data[3] = y1 + ST7735_YSTART;
    ST7735_WriteData(data, sizeof(data));

    // write to RAM
    ST7735_WriteCommand(ST7735_RAMWR);
}

void ST7735_Init() {
  GPIOB->CRH = (GPIOB->CRH & ~( GPIO_CRH_MODE14_Msk | GPIO_CRH_CNF14_Msk
                              | GPIO_CRH_MODE13_Msk | GPIO_CRH_CNF13_Msk
                              | GPIO_CRH_MODE12_Msk | GPIO_CRH_CNF12_Msk ))
             | GPIO_CRH_MODE14_1
             | GPIO_CRH_MODE13_1
             | GPIO_CRH_MODE12_1
             ;
  GPIOB->BSRR = GPIO_BSRR_BR13;
  ST7735_Unselect();
  delay_ms(50);
  ST7735_Select();
  ST7735_Reset();
  ST7735_ExecuteCommandList(init_cmds1);
  ST7735_ExecuteCommandList(init_cmds2);
  ST7735_ExecuteCommandList(init_cmds3);
  ST7735_Unselect();
}

void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
        return;

    ST7735_Select();

    ST7735_SetAddressWindow(x, y, x+1, y+1);
    color = (color >> 8) | ((color & 0xFF) << 8);
    ST7735_WriteData((uint8_t *)&color, sizeof(color));

    ST7735_Unselect();
}

static void ST7735_WriteChar(uint16_t x, uint16_t y, display_char_s * a_data) {
  bool v_last_row = false;
  uint32_t bytes_to_write = a_data->m_cols_count * sizeof(uint16_t);

  uint16_t line_buf1[32]; // max font width
  uint16_t line_buf2[32]; // max font width
  
  ST7735_SetAddressWindow(x, y, x+a_data->m_symbol->m_x_advance-1, y+a_data->m_font->m_row_height-1);
  GPIOB->BSRR = GPIO_BSRR_BS14;

  // write line 1
  a_data->m_pixbuf = line_buf1;
  v_last_row = display_char_row( a_data );
  ST7735_spi_write_start((uint8_t *)line_buf1, bytes_to_write);
  //
  while ( !v_last_row ) {
    // write line 2
    a_data->m_pixbuf = line_buf2;
    v_last_row = display_char_row( a_data );
    ST7735_spi_write_end();
    ST7735_spi_write_start((uint8_t *)line_buf2, bytes_to_write);
    if ( v_last_row ) {
      break;
    }
    // write line 1
    a_data->m_pixbuf = line_buf1;
    v_last_row = display_char_row( a_data );
    ST7735_spi_write_end();
    ST7735_spi_write_start((uint8_t *)line_buf1, bytes_to_write);
  }
  // end wait
  ST7735_spi_write_end();
}


void ST7735_WriteString(uint16_t x, uint16_t y, const char* str, const packed_font_desc_s & fnt, uint16_t color, uint16_t bgcolor) {
    bool v_used = false;
    display_char_s v_ds;

    ST7735_Select();

    while(*str) {
        if ( !v_used ) {
          v_used = true;
          display_char_init( &v_ds, *str, &fnt, 0, bgcolor, color );
        } else {
          display_char_init2( &v_ds, *str );
        }
        
        if(x + v_ds.m_symbol->m_x_advance >= ST7735_WIDTH) {
            x = 0;
            y += v_ds.m_font->m_row_height;
            
            if(y + v_ds.m_font->m_row_height >= ST7735_HEIGHT) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        ST7735_WriteChar(x, y, &v_ds);
        x += v_ds.m_symbol->m_x_advance;
        str++;
    }

    ST7735_Unselect();
}

void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) w = ST7735_WIDTH - x;
    if((y + h - 1) >= ST7735_HEIGHT) h = ST7735_HEIGHT - y;

    ST7735_Select();
    ST7735_SetAddressWindow(x, y, x+w-1, y+h-1);

    color = (color >> 8) | ((color & 0xFF) << 8);
    GPIOB->BSRR = GPIO_BSRR_BS14;
    for(y = h; y > 0; y--) {
        for(x = w; x > 0; x--) {
            ST7735_spi_write( (uint8_t *)&color, sizeof(color) );
        }
    }

    ST7735_Unselect();
}

void ST7735_FillRectangleFast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) {
      w = ST7735_WIDTH - x;
    }
    if((y + h - 1) >= ST7735_HEIGHT) {
      h = ST7735_HEIGHT - y;
    }

    ST7735_Select();
    ST7735_SetAddressWindow(x, y, x+w-1, y+h-1);

    // Prepare whole line in a single buffer
    color = (color >> 8) | ((color & 0xFF) << 8);
    uint16_t line[ST7735_MAX_LINE_PIXELS];
    for(x = 0; x < w; ++x) {
      line[x] = color;
    }

    GPIOB->BSRR = GPIO_BSRR_BS14;
    uint32_t line_bytes = w * sizeof(color);
    for(y = h; y > 0; y--) {
        ST7735_spi_write( (uint8_t *)line, line_bytes );
    }

    ST7735_Unselect();
}

void ST7735_FillScreen(uint16_t color) {
    ST7735_FillRectangle(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}

void ST7735_FillScreenFast(uint16_t color) {
    ST7735_FillRectangleFast(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}


void ST7735_DrawImage(int x, int y, int w, int h, const uint8_t * a_data, int a_data_len) {
  uint8_t v_image_line1[ST7735_WIDTH * sizeof(uint16_t)];
  uint8_t v_image_line2[ST7735_WIDTH * sizeof(uint16_t)];
  if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
  if((x + w - 1) >= ST7735_WIDTH) return;
  if((y + h - 1) >= ST7735_HEIGHT) return;
  uint32_t v_row_bytes = w * sizeof(uint16_t);

  zic_decompress_state_s v_st;
  zic_decompress_init( a_data, a_data_len, v_image_line1, w, h, v_st );

  ST7735_Select();
  ST7735_SetAddressWindow((uint8_t)x, (uint8_t)y, (uint8_t)(x+w-1), (uint8_t)(y+h-1));

  GPIOB->BSRR = GPIO_BSRR_BS14;

  if ( h > 0 ) {
    if ( zic_decompress_row( v_st ) ) {
      ST7735_spi_write_start( v_image_line1, v_row_bytes );
      for ( --h; h > 0; --h ) {
        v_st.m_row_ptr = v_image_line2;
        if ( zic_decompress_row( v_st ) ) {
          ST7735_spi_write_end();
          ST7735_spi_write_start( v_image_line2, v_row_bytes );
        } else {
          break;
        }
        if ( --h <= 0 ) {
          break;
        }
        v_st.m_row_ptr = v_image_line1;
        if ( zic_decompress_row( v_st ) ) {
          ST7735_spi_write_end();
          ST7735_spi_write_start( v_image_line1, v_row_bytes );
        } else {
          break;
        }
      }
    }
    ST7735_spi_write_end();
  }
  
  ST7735_Unselect();
}

void ST7735_InvertColors(int invert) {
    ST7735_Select();
    ST7735_WriteCommand(invert ? ST7735_INVON : ST7735_INVOFF);
    ST7735_Unselect();
}

void ST7735_SetGamma(uint8_t gamma)
{
	ST7735_Select();
	ST7735_WriteCommand(ST7735_GAMSET);
	ST7735_WriteData(&gamma, sizeof(gamma));
	ST7735_Unselect();
}
