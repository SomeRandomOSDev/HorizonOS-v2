#pragma once

#include "textio.h"
#include "memory.h"

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

void printChar(char c)
{
    text_cursor_pos %= 80 * 25;
    switch(c)
    {
    case 0:
        break;
    case '\n':
        text_cursor_pos += 80;
    case '\r':
        text_cursor_pos /= 80;
        text_cursor_pos *= 80;
        break;
    case '\b':
        text_cursor_pos--;
        // if((*((char*)0xb8000 + 2 * text_cursor_pos)) == 255)
        //     text_cursor_pos -= (TAB_LENGTH - 1);
        printChar(' ');
        text_cursor_pos--;
        break;
    case 127:
        // printChar(' ');
        // text_cursor_pos--;
        break;
    case 27:
        break;
    case '\t':
        // for(unsigned int i = 0; i < TAB_LENGTH; i++)
        //     printChar(255);
        printChar(' ');
        break;
    default:
        *((char*)0xb8000 + 2 * text_cursor_pos) = c;
        *((char*)0xb8001 + 2 * text_cursor_pos) = text_color;
        text_cursor_pos++;
    }

    text_cursor_pos %= 80 * 25;
}

void putc(char c)
{
    printChar(c);

    UpdateCursor();
}

void puts(const char* str)
{
    unsigned int i = 0;
    while(str[i] != 0)
    {
        printChar(str[i]);
        i++;
    }

    UpdateCursor();
}

char* hex = "0123456789abcdef";
char* HEX = "0123456789ABCDEF";

void printf(const char* fmt, ...)
{
    uint32_t* argp = (uint32_t*)&fmt;
    argp++;
    for(uint32_t i = 0; fmt[i] != '\0'; i++)
    {
        char currChar = fmt[i];
        if(currChar == '%')
        {
            switch (fmt[i + 1])
            {
            case '%':
                putc('%');
                break;

            case 'c':
                putc((char)*argp);
                argp++;
                break;

            case 's':
                puts((char*)*argp);
                argp++;
                break;

            case 'i':
                int32_t i_number = (int32_t)*argp;

                if(i_number == 0) 
                {
                    putc('0');
                    break;
                }

                uint8_t i_length = 0;
                
                if(i_number < 0)
                {
                    putc('-');
                    i_number *= -1;
                }

                int32_t i_number2 = i_number;

                while(i_number2 >= 1)
                {
                    i_number2 /= 10;
                    i_length++;
                }

                char* i_string = (char*)malloc((i_length + 1) * sizeof(char));

                i_number2 = i_number;

                for(uint8_t j = 0; i_number2 >= 1; j++)
                {
                    i_string[i_length - j - 1] = '0' + (i_number2 % 10);
                    i_number2 /= 10;
                }

                i_string[i_length] = '\0';
                
                puts(i_string);
                free(i_string);

                argp++;
                break;

            case 'u':
                uint32_t u_number = (uint32_t)*argp;

                if(u_number == 0) 
                {
                    putc('0');
                    break;
                }

                uint8_t u_length = 0;

                uint32_t u_number2 = u_number;

                while(u_number2 >= 1)
                {
                    u_number2 /= 10;
                    u_length++;
                }

                char* u_string = (char*)malloc((u_length + 1) * sizeof(char));

                u_number2 = u_number;

                for(uint8_t j = 0; u_number2 >= 1; j++)
                {
                    u_string[u_length - j - 1] = '0' + (u_number2 % 10);
                    u_number2 /= 10;
                }

                u_string[u_length] = '\0';
                
                puts(u_string);
                free(u_string);

                argp++;
                break;

            case 'x':
                uint32_t x_number = (uint32_t)*argp;

                char* x_string = (char*)malloc((8 + 1) * sizeof(char));

                memset(x_string, '0', 8);

                for(uint8_t j = 0; j < 8; j++)
                {
                    x_string[8 - j - 1] = hex[x_number % 16];
                    x_number >>= 4;
                }

                x_string[8] = '\0';
                
                puts(x_string);
                free(x_string);

                argp++;
                break;

            case 'X':
                uint32_t X_number = (uint32_t)*argp;

                char* X_string = (char*)malloc((8 + 1) * sizeof(char));

                memset(X_string, '0', 8);

                for(uint8_t j = 0; j < 8; j++)
                {
                    X_string[8 - j - 1] = HEX[X_number % 16];
                    X_number >>= 4;
                }

                X_string[8] = '\0';
                
                puts(X_string);
                free(X_string);

                argp++;
                break;
            
            default:
                putc('%');
                putc(fmt[i + 1]);
                break;
            }
            i++;
        }
        else
            putc(currChar);
    }
}