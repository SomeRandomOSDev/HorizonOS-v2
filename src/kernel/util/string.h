#pragma once

void* memcpy(void* dest, const void* src, size_t size)
{
	for(uint32_t i = 0; i < size; i++)
		*((uint8_t*)dest + i) = *((uint8_t*)src + i);
	return dest;
}

void memset(void* ptr, uint8_t val, uint32_t size)
{
	for(uint32_t i = 0; i < size; i++)
		*((uint8_t*)ptr + i) = val;
}

size_t strlen(const char* str)
{
    size_t length = 0;
    while(str[length] != 0)
        length++;
    return length;
}

bool memcmp(void* str, void* str2, size_t size)
{
	bool r = false;
	for(uint32_t i = 0; i < size; i++)
		r |= (((uint8_t*)str)[i] == ((uint8_t*)str2)[i]);
	return !r;
}

char* strcpy(char *dest, const char *src)
{
	uint32_t i = 0;
	while(src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return dest;
}

bool strcmp(char* str, char* str2)
{
	bool r = false;
	for(uint32_t i = 0; str[i] != '\0' && str2[i] != '\0'; i++)
		r |= (str[i] == str2[i]);
	return !r;
}