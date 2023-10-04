#pragma once

#include "../util/string.h"
#include "../util/defs.h"

void EnableInterrupts()
{asm("sti");}
void DisableInterrupts()
{asm("cli");}
void Halt()
{DisableInterrupts(); asm("hlt");}

#pragma pack(1)
struct IDTEntry
{
    uint16_t base_lo;  // 0 - bits 0 - 15
    uint16_t ksegment; // 2
    uint8_t zero;      // 4
    uint8_t flags;     // 5
    uint16_t base_hi;  // 6 - bits 16 - 31
};

#pragma pack(1)
struct IDTptr
{
    uint16_t limit;
    uint32_t base;
};

struct IDTptr _idtr;
struct IDTEntry idt[256];

extern void LoadIDT();

void CreateIDTEntry(uint8_t id, uint32_t base, uint16_t segment, uint8_t flags)
{
    idt[id].base_lo = (base & 0xffff);
    idt[id].base_hi = (base >> 16);
    idt[id].flags = flags;
    idt[id].ksegment = segment;
    idt[id].zero = 0;
}

void kpanic(const char* text)
{
    ClearScreen(BG_LIGHTBLUE);
    SetCursorPos(4, 2);
    DisableCursor();
    SetTextColor(FG_LIGHTRED | BG_LIGHTBLUE);
    puts("Kernel panic\n\n\t");
    SetTextColor(FG_WHITE | BG_LIGHTBLUE);
    puts(text);
    Halt();
}

void ISR0()
{
    kpanic(
   "Interrupt number: 0\n\
    Error: DIVISION_BY_ZERO");
}

void SetUpIDT()
{
    _idtr.base = (uint32_t)&idt;
    _idtr.limit = sizeof(struct IDTEntry) * 256 - 1;

    memset(&idt, 0, sizeof(struct IDTEntry) * 256);

    CreateIDTEntry(0, (uint32_t)&ISR0, 0x08, 0x8e);

    LoadIDT();
}