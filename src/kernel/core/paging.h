#pragma once

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t page_table_0[1024] __attribute__((aligned(4096)));
uint32_t page_table_4[1024] __attribute__((aligned(4096)));

extern void LoadPageDirectory(uint32_t address);
extern void EnablePaging();
extern void DisablePaging();
extern uint32_t GetCR2();

void InitPageDirectory()
{
    for(uint16_t i = 0; i < 1024; i++)
    {
        page_directory[i] = 0b10;
    }

    for(uint16_t i = 0; i < 1024; i++)
    {
        uint32_t address = i * 4096;
        page_table_0[i] = address | 0b11;
    }

    for(uint16_t i = 0; i < 1024; i++)
    {
        uint32_t address = (i + 4 * 1024) * 4096;
        page_table_4[i] = address | 0b11;
    }

    page_directory[0] = ((uint32_t)page_table_0) | 0b11;
    page_directory[4] = ((uint32_t)page_table_4) | 0b11;

    LoadPageDirectory((uint32_t)page_directory);
    EnablePaging();
}