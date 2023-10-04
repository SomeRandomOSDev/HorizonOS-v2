#pragma once

#include "textio.h"

void SetTextColor(uint8_t color)
{
    text_color = color;
}

void SetCursorPos(uint8_t x, uint8_t y)
{
    text_cursor_pos = (y % 25) * 80 + (x % 80);

    UpdateCursor();
}

uint16_t GetCursorPos()
{
    uint16_t pos = 0;
    outb(0x3d4, 0x0f);
    pos |= inb(0x3d5);
    outb(0x3d4, 0x0e);
    pos |= ((uint16_t)inb(0x3d5)) << 8;
    return pos;
}


void EnableCursor(uint8_t topScanLine, uint8_t lowScanLine) // minScanLine = 0 || maxScanLine = 15
{
	outb(0x3d4, 0x0a);
	outb(0x3d5, (inb(0x3d5) & 0xc0) | topScanLine);
 
	outb(0x3d4, 0x0b);
	outb(0x3d5, (inb(0x3d5) & 0xe0) | lowScanLine);
}

void DisableCursor()
{
	outb(0x3d4, 0x0a);
	outb(0x3d5, 0x20);
}

void UpdateCursor()
{ 
	outb(0x3d4, 0x0f);
	outb(0x3d5, (uint8_t) (text_cursor_pos & 0xff));
	outb(0x3d4, 0x0e);
	outb(0x3d5, (uint8_t) ((text_cursor_pos >> 8) & 0xff));
}

void ClearScreen(uint8_t color)
{
    for(unsigned int  i = 0; i < 80 * 25; i++)
    {
        *((uint8_t*)0xb8000 + 2 * i) = ' ';
        *((uint8_t*)0xb8001 + 2 * i) = color;
    }
}

void putc(char c)
{
    switch(c)
    {
    case '\n':
        text_cursor_pos += 80;
    case '\r':
        text_cursor_pos /= 80;
        text_cursor_pos *= 80;
        break;
    case '\t':
        for(unsigned int i = 0; i < TAB_LENGTH; i++)
            putc(' ');
        break;
    default:
        *((char*)0xb8000 + 2 * text_cursor_pos) = c;
        *((char*)0xb8001 + 2 * text_cursor_pos) = text_color;
        text_cursor_pos++;
    }

    UpdateCursor();
}

void puts(const char* str)
{
    unsigned int i = 0;
    while(str[i] != 0)
    {
        putc(str[i]);
        i++;
    }
}