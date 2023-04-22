#ifndef __ST7735_H__
#define __ST7735_H__

#include "test32.h"
#include "utils/zic_utils.h"

#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MV  0x20
#define ST7735_MADCTL_ML  0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH  0x04


#define ST7735_MAX_LINE_PIXELS   160

// AliExpress/eBay 1.8" display, default orientation

#define ST7735_IS_160X128 1
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 128
#define ST7735_XSTART 0
#define ST7735_YSTART 0
// Frame Data Write Direction According to the MADCTL parameters (MV, MX and MY), from ST7735 datasheet
#define ST7735_ROTATION (ST7735_MADCTL_MV | ST7735_MADCTL_MY) // X-Y exchange (160 width, 128 height) and Y-mirror


/****************************/

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_GAMSET  0x26
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define ST7735_COLOR565(r, g, b) ((uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3)))
#define	ST7735_BLACK   0x0000
#define	ST7735_BLUE    0x001F
#define	ST7735_RED     0xF800
#define	ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF
#define ST7735_LGRAY   0xA514
#define ST7735_FOX     0xFC40
#define ST7735_LBLUE   0x039F
#define ST7735_LEAF    ST7735_COLOR565(0x34, 0xAE, 0x6D)

typedef enum {
	GAMMA_10 = 0x01,
	GAMMA_25 = 0x02,
	GAMMA_22 = 0x04,
	GAMMA_18 = 0x08
} GammaDef;

// call before initializing any SPI devices
void ST7735_Unselect();

void ST7735_Init(void);
void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7735_WriteString(uint16_t x, uint16_t y, const char* str, const packed_font_desc_s & fnt, uint16_t color, uint16_t bgcolor);
void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7735_FillRectangleFast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7735_FillScreen(uint16_t color);
void ST7735_FillScreenFast(uint16_t color);
void ST7735_DrawImage(int x, int y, int w, int h, const uint8_t* a_data, int a_data_len);
void ST7735_InvertColors(int invert); // 0 - false, != 0 - true
void ST7735_SetGamma(GammaDef gamma);
void ST7735_WriteStringWithBackground(
              int a_x
            , int a_y
            , int a_width
            , int a_height
            , const char * a_str
            , const packed_font_desc_s & a_fnt
            , uint16_t a_color
            , uint16_t a_bgcolor
            );


#endif // __ST7735_H__
