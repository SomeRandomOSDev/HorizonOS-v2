#pragma once

void* memcpy(void* dest, const void* src, size_t size)
{
    for(unsigned int i = 0; i < size; i++)
        ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];

    return dest;
}

void* memset(void* ptr, int value, size_t count)
{
    for(unsigned int i = 0; i < count; i++)
        ((uint8_t*)ptr)[i] = value;
    return ptr;
}

size_t strlen(const char* str)
{
    size_t length = 0;
    while(str[length] != 0)
        length++;
    return length;
}