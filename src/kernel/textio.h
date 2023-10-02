#pragma once

#define FG_BLACK         0x00
#define FG_BLUE          0x01
#define FG_GREEN         0x02
#define FG_CYAN          0x03
#define FG_RED           0x04
#define FG_MAGENTA       0x05
#define FG_BROWN         0x06
#define FG_LIGHTGRAY     0x07
#define FG_DARKGRAY      0x08
#define FG_LIGHTBLUE     0x09
#define FG_LIGHTGREEN    0x0a
#define FG_LIGHTCYAN     0x0b
#define FG_LIGHTRED      0x0c
#define FG_LIGHTMAGENTA  0x0d
#define FG_YELLOW        0x0e
#define FG_WHITE         0x0f
 
#define BG_BLACK         0x00
#define BG_BLUE          0x10
#define BG_GREEN         0x20
#define BG_CYAN          0x30
#define BG_RED           0x40
#define BG_MAGENTA       0x50
#define BG_BROWN         0x60
#define BG_LIGHTGRAY     0x70
#define BG_DARKGRAY      0x80
#define BG_LIGHTBLUE     0x90
#define BG_LIGHTGREEN    0xa0
#define BG_LIGHTCYAN     0xb0
#define BG_LIGHTRED      0xc0
#define BG_LIGHTMAGENTA  0xd0
#define BG_YELLOW        0xe0
#define BG_WHITE         0xf0

#define TAB_LENGTH       4

uint16_t text_cursor_pos = 0;
uint8_t text_color = FG_WHITE | BG_BLACK;

void SetTextColor(uint8_t color);
void SetCursorPos(uint8_t x, uint8_t y);

uint16_t GetCursorPos();
void EnableCursor(uint8_t topScanLine, uint8_t lowScanLine);
void DisableCursor();
void UpdateCursor();

void putc(char c);
void puts(char* str);