#pragma once

struct GDTEntry
{
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMiddle;
    uint8_t access;
    uint8_t granularity;
    uint8_t baseHigh;
} __attribute__((packed));

struct GDTPtr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct GDTEntry GDT[3];
struct GDTPtr gdtPtr;

extern void LoadGDT();

void GDTSetGate(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    GDT[num].baseLow = (base & 0xffff);
    GDT[num].baseMiddle = ((base & 0xff0000) >> 16);
    GDT[num].baseHigh = ((base & 0xff000000) >> 24);

    GDT[num].limitLow = (limit & 0xffff);
    GDT[num].granularity = ((limit & 0x0f0000) >> 16);

    GDT[num].granularity |= (gran & 0xf0);
    GDT[num].access = access;
}

void SetUpGDT()
{
    gdtPtr.limit = (sizeof(struct GDTEntry) * 3) - 1;
    gdtPtr.base = (uint32_t)&GDT;

    GDTSetGate(0, 0, 0, 0, 0);

    GDTSetGate(1, 0, 0xffffffff, 0x9a, 0xcf);

    GDTSetGate(2, 0, 0xffffffff, 0x92, 0xcf);

    LoadGDT();
}