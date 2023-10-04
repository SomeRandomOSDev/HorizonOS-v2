#pragma once

#include "../util/defs.h"

#pragma pack(1)
struct GDTEntry
{
    uint16_t limit_lo;    // 0 - bits 0 - 15
    uint16_t base_lo;     // 2 - bits 0 - 15
    uint8_t base_middle;  // 4 - bits 16 - 23
    uint8_t access;       // 5
    uint8_t limit_hi;     // 6 - bits 16 - 29
    uint8_t base_hi;      // 7 - bits 24 - 31
};

void CreateGDTEntry(struct GDTEntry* entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{ 
    entry->limit_lo = (limit & 0xff);
    entry->limit_hi = ((limit >> 16) & 0x0f);
 
    entry->base_lo = (base & 0xffff);
    entry->base_middle = ((base >> 16) & 0xff);
    entry->base_hi = ((base >> 24) & 0xff);
 
    entry->access = access;
 
    entry->limit_hi |= (flags << 4);
}

struct GDTEntry GDT_entries[3];

extern void LoadGDT(uint16_t limit, uint32_t base);

void SetUpGDT()
{
    CreateGDTEntry(&GDT_entries[0], 0, 0, 0, 0);
    CreateGDTEntry(&GDT_entries[1], 0x100000, 0x003FFFFF, 0x9a, 0xc);
    CreateGDTEntry(&GDT_entries[2], 0x500000, 0x003FFFFF, 0x92, 0xc);

    LoadGDT(sizeof(struct GDTEntry) * 3 - 1, (uint32_t)&GDT_entries);
}