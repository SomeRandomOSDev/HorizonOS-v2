#pragma once

void putc(char c)
{
    *((char*)0xb8000) = c;
    *((char*)0xb8001) = 0x0f;
}