#include "stm32f103x6.h"
#include "bme280.h"
#include "st7735.h"
#include "temp_plus.h"
#include "temp_minus.h"
#include "pressure_meter.h"
#include "humidity.h"
#include "flag.h"
#include "test32.h"

#include <stdio.h>


extern volatile uint32_t g_milliseconds;


void delay_ms( uint32_t a_ms ) {
  uint32_t a_from = g_milliseconds;
  while ( ((uint32_t)(g_milliseconds - a_from)) < a_ms ) {}
}


extern "C" {
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
}




void run() {
  // at start clock source = HSI
  // configure RCC: 8 MHz HSE + PLL x9 = 72 MHz
  // enable HSE
  RCC->CR |= RCC_CR_HSEON;
  // wait for HSE starts
  while ( 0 == (RCC->CR & RCC_CR_HSERDY) ) {}
  // FLASH latency 1
  FLASH->ACR = FLASH_ACR_PRFTBE
             | FLASH_ACR_LATENCY_2
             ;
  // clock params: PLL = (HSE/1)*9, AHB = PLL/1, APB1 = PLL/2, APB2 = PLL/1
  RCC->CFGR = RCC_CFGR_SW_HSI
            | RCC_CFGR_HPRE_DIV1
            | RCC_CFGR_PPRE1_DIV2
            | RCC_CFGR_PPRE2_DIV1
            | RCC_CFGR_ADCPRE_DIV2
            | RCC_CFGR_PLLSRC
            | RCC_CFGR_PLLXTPRE_HSE
            | RCC_CFGR_PLLMULL9
            | RCC_CFGR_USBPRE
            | RCC_CFGR_MCO_NOCLOCK
            ;
  // enable PLL
  RCC->CR |= RCC_CR_PLLON;
  // wait for PLL starts
  while ( 0 == (RCC->CR & RCC_CR_PLLRDY) ) {}
  // switch clock source from HSI to PLL, it works because SW_HSI = 0
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  // now clock at 72 MHz, AHB 72 MHz, APB1 36 MHz, APB2 72 MHz
  uint32_t * v_from = (uint32_t *)&_sidata;
  uint32_t * v_to = (uint32_t *)&_sdata;
  uint32_t * v_end = (uint32_t *)&_edata;
  while ( v_to < v_end ) {
    *v_to++ = *v_from++;
  }
  v_to = (uint32_t *)&_sbss;
  v_end = (uint32_t *)&_ebss;
  while ( v_to < v_end ) {
    *v_to++ = 0;
  }
  // enable clock for PIOC
  // GPIOB and I2C1 clock enable
  // enable clock for SPI1
  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
  RCC->APB2ENR |= ( RCC_APB2ENR_IOPBEN
                  | RCC_APB2ENR_IOPCEN
                  | RCC_APB2ENR_IOPAEN
                  | RCC_APB2ENR_USART1EN
                  | RCC_APB2ENR_SPI1EN
                  );
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;
  // PIOC13 - output push-pull, low speed
  GPIOC->CRH = (GPIOC->CRH & ~(GPIO_CRH_MODE13_Msk | GPIO_CRH_CNF13_Msk))
               | GPIO_CRH_MODE13_1
               ;
  // USART1 115200 8N1
  // 48E6 / 16 / 39.0625 ~= 115200
  USART1->BRR = (39 << USART_BRR_DIV_Mantissa_Pos) | (1 << USART_BRR_DIV_Fraction_Pos);
  USART1->CR3 = 0;
  USART1->CR2 = 0;
  USART1->CR1 = USART_CR1_TE
              | USART_CR1_UE
              ;
  // PIOA9 - output push-pull alternate fn USART1 TX
  GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_MODE9_Msk | GPIO_CRH_CNF9_Msk))
               | GPIO_CRH_MODE9_1
               | GPIO_CRH_CNF9_1
               ;
  //
  printf( "Hello from china STM32F103C6 clone!\n" );
  // GPIO first
  // PIOA7 - output push-pull alternate fn SPI1 MOSI
  // PIOA5 - output push-pull alternate fn SPI1 SCK
  GPIOA->CRL = (GPIOA->CRL & ~( GPIO_CRL_MODE7_Msk | GPIO_CRL_CNF7_Msk
                              | GPIO_CRL_MODE5_Msk | GPIO_CRL_CNF5_Msk ))
             | GPIO_CRL_MODE7_0 | GPIO_CRL_CNF7_1
             | GPIO_CRL_MODE5_0 | GPIO_CRL_CNF5_1
             ;
  // SPI1 master, 72E6 / 8 = 9 MHz SCK
  SPI1->CR1 = SPI_CR1_MSTR
            | SPI_CR1_BR_1
            | SPI_CR1_SPE
            | SPI_CR1_SSI
            | SPI_CR1_SSM
            ;
  // prepare constants for SPI1 -> DMA
  SPI1->CR2 = SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN;
  DMA1_Channel2->CPAR = (uint32_t)&SPI1->DR;
  DMA1_Channel3->CPAR = (uint32_t)&SPI1->DR;
  // SysTick interrupt for each millisecond
  SysTick_Config( 9000 );
  // init display
  ST7735_Init();
  ST7735_DrawImage( 0, 0, Iflag_tga_width, Iflag_tga_height, Iflag_tga_zic, sizeof(Iflag_tga_zic) );
  //
  bool v_bme_ok = BMP280_init();
  if ( !v_bme_ok ) {
    printf( "BME280 module error\n" );
  }
  //
  delay_ms( 2500 );
  //
  ST7735_FillScreenFast(ST7735_BLACK);
  // print Hello
  const char * v_hello1 = "Привет!";
  const char * v_hello2 = "¡Hola!";
  const char * v_hello3 = "嗨!";
  const char * v_hello4 = "Hello!";
  //
  int v_width, v_height;
  int v_x1, v_x2, v_x3, v_x4;
  get_text_extent( &test32_font, v_hello1, &v_width, &v_height );
  v_x1 = (ST7735_WIDTH - v_width) / 2;
  get_text_extent( &test32_font, v_hello2, &v_width, &v_height );
  v_x2 = (ST7735_WIDTH - v_width) / 2;
  get_text_extent( &test32_font, v_hello3, &v_width, &v_height );
  v_x3 = (ST7735_WIDTH - v_width) / 2;
  get_text_extent( &test32_font, v_hello4, &v_width, &v_height );
  v_x4 = (ST7735_WIDTH - v_width) / 2;
  //  
  for ( int i = 0x01; i < 0xF8; i += 3 ) {
    int k = i + 7;
    uint16_t v_color = (uint16_t)(((k & 0xF8) << 8) | ((k & 0xF8) << 3) | ((k & 0xF8) >> 3));
    ST7735_WriteString( v_x1, 0, v_hello1, test32_font, v_color, 0 );
    ST7735_WriteString( v_x2, 32, v_hello2, test32_font, 0, 0 );
    ST7735_WriteString( v_x3, 64, v_hello3, test32_font, 0, 0);
    ST7735_WriteString( v_x4, 96, v_hello4, test32_font, 0, 0 );
  }
  for ( int i = 0x01; i < 0xF8; i += 3 ) {
    int k = 0xFF - i;
    int k2 = i + 7;
    uint16_t v_color = (uint16_t)(((k & 0xF8) << 8) | ((k & 0xF8) << 3) | ((k & 0xF8) >> 3));
    uint16_t v_color2 = (uint16_t)(((k2 & 0xF8) << 8) | ((k2 & 0xF8) << 3) | ((k2 & 0xF8) >> 3));
    ST7735_WriteString( v_x1, 0, v_hello1, test32_font, v_color, 0 );
    ST7735_WriteString( v_x2, 32, v_hello2, test32_font, v_color2, 0 );
    ST7735_WriteString( v_x3, 64, v_hello3, test32_font, 0, 0 );
    ST7735_WriteString( v_x4, 96, v_hello4, test32_font, 0, 0 );
  }
  for ( int i = 0x01; i < 0xF8; i += 3 ) {
    int k = 0xFF - i;
    int k2 = i + 7;
    uint16_t v_color = (uint16_t)(((k & 0xF8) << 8) | ((k & 0xF8) << 3) | ((k & 0xF8) >> 3));
    uint16_t v_color2 = (uint16_t)(((k2 & 0xF8) << 8) | ((k2 & 0xF8) << 3) | ((k2 & 0xF8) >> 3));
    ST7735_WriteString( v_x1, 0, v_hello1, test32_font, 0, 0 );
    ST7735_WriteString( v_x2, 32, v_hello2, test32_font, v_color, 0 );
    ST7735_WriteString( v_x3, 64, v_hello3, test32_font, v_color2, 0 );
    ST7735_WriteString( v_x4, 96, v_hello4, test32_font, 0, 0 );
  }
  for ( int i = 0x01; i < 0xF8; i += 3 ) {
    int k = 0xFF - i;
    int k2 = i + 7;
    uint16_t v_color = (uint16_t)(((k & 0xF8) << 8) | ((k & 0xF8) << 3) | ((k & 0xF8) >> 3));
    uint16_t v_color2 = (uint16_t)(((k2 & 0xF8) << 8) | ((k2 & 0xF8) << 3) | ((k2 & 0xF8) >> 3));
    ST7735_WriteString( v_x1, 0, v_hello1, test32_font, 0, 0 );
    ST7735_WriteString( v_x2, 32, v_hello2, test32_font, 0, 0 );
    ST7735_WriteString( v_x3, 64, v_hello3, test32_font, v_color, 0 );
    ST7735_WriteString( v_x4, 96, v_hello4, test32_font, v_color2, 0 );
  }
  for ( int i = 0x01; i < 0xF8; i += 3 ) {
    int k = 0xFF - i;
    uint16_t v_color = (uint16_t)(((k & 0xF8) << 8) | ((k & 0xF8) << 3) | ((k & 0xF8) >> 3));
    ST7735_WriteString( v_x1, 0, v_hello1, test32_font, 0, 0 );
    ST7735_WriteString( v_x2, 32, v_hello2, test32_font, 0, 0 );
    ST7735_WriteString( v_x3, 64, v_hello3, test32_font, 0, 0 );
    ST7735_WriteString( v_x4, 96, v_hello4, test32_font, v_color, 0 );
  }
  //
  delay_ms( 500 );
  // draw constant icons
  ST7735_DrawImage( 0, 44, Ipressure_meter_tga_width, Ipressure_meter_tga_height, Ipressure_meter_tga_zic, (int)sizeof(Ipressure_meter_tga_zic) );
  if ( v_bme_ok && BMP280_is_BME() ) {
    ST7735_DrawImage( 3, 84, Ihumidity_tga_width, Ihumidity_tga_height, Ihumidity_tga_zic, (int)sizeof(Ihumidity_tga_zic) );
  }
  //
  uint8_t v_buf[80];
  int v_t, v_p, v_h, v_t_last = -999999, v_p_last = -999999, v_h_last = -999999;
  for (;;) {
    if ( v_bme_ok ) {
      // read meters
      if ( BMP280_readMesure( &v_t, &v_p, &v_h ) ) {
        // prepare values
        v_p = (v_p * 10000) / 133322;
        v_p = (v_p + 5) / 10;
        char v_char_sign = '+';
        if ( v_t < 0 ) {
          v_t = 0 - v_t;
          v_char_sign = '-';
        }
        v_t = (v_t + 5) / 10;
        // terminal output
        if ( BMP280_is_BME() ) {
          printf( "t = %c%d.%d C, p = %d mmHg, h = %d%%\n", v_char_sign, v_t / 10, v_t % 10, v_p, v_h );
        } else {
          printf( "t = %c%d.%d C, p = %d mmHg\n", v_char_sign, v_t / 10, v_t % 10, v_p );
        }
        // display values
        char * v_line = (char *)v_buf;
        // temperature
        if ( v_t_last != v_t ) {
          v_t_last = v_t;
          if ( '-' == v_char_sign ) {
            ST7735_DrawImage( 6, 0, Itemp_minus_tga_width, Itemp_minus_tga_height, Itemp_minus_tga_zic, (int)sizeof(Itemp_minus_tga_zic) );
          } else {
            ST7735_DrawImage( 6, 0, Itemp_plus_tga_width, Itemp_plus_tga_height, Itemp_plus_tga_zic, (int)sizeof(Itemp_plus_tga_zic) );
          }
          sprintf( v_line, "%c%d.%d", v_char_sign, v_t / 10, v_t % 10 );
          //
          ST7735_WriteStringWithBackground(
                    45
                  , 6
                  , 115
                  , 32
                  , v_line
                  , test32_font
                  , '+' == v_char_sign ? ST7735_FOX : ST7735_LBLUE
                  , ST7735_BLACK
                  );
        }
        // pressure
        if ( v_p_last != v_p ) {
          v_p_last = v_p;
          sprintf( v_line, "%d", v_p );
          //
          ST7735_WriteStringWithBackground(
                    45
                  , 48
                  , 115
                  , 32
                  , v_line
                  , test32_font
                  , ST7735_LGRAY
                  , ST7735_BLACK
                  );
        }
        // humidity
        if ( BMP280_is_BME() ) {
          if ( v_h_last != v_h ) {
            v_h_last = v_h;
            sprintf( v_line, "%d%%", v_h );
            //
            ST7735_WriteStringWithBackground(
                      45
                    , 90
                    , 115
                    , 32
                    , v_line
                    , test32_font
                    , ST7735_LEAF
                    , ST7735_BLACK
                    );
          }
        }
      }
    }
    delay_ms( 500 );
    GPIOC->BSRR = GPIO_BSRR_BR13;
    delay_ms( 500 );
    GPIOC->BSRR = GPIO_BSRR_BS13;
  }
}
