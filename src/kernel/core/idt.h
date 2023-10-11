#pragma once

void EnableInterrupts()
{asm("sti");}
void DisableInterrupts()
{asm("cli");}
void Halt()
{DisableInterrupts(); asm("hlt");}

#include "../util/string.h"
#include "pic.c"
#include "pit.h"
#include "PS2/keyboard.c"

struct IDTEntry
{
    uint16_t base_lo;  // 0 - bits 0 - 15
    uint16_t ksegment; // 2
    uint8_t zero;      // 4
    uint8_t flags;     // 5
    uint16_t base_hi;  // 6 - bits 16 - 31
} __attribute__((packed));

struct IDTptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct Registers
{
    unsigned int gs, fs, es, ds; 
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  
    unsigned int interruptNumber, errorCode;   
    unsigned int eip, cs, eflags, useresp, ss;  
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

void kpanic(uint8_t intNb, uint8_t errorCode, const char* errorText)
{
    DisableInterrupts();
    ClearScreen(BG_LIGHTBLUE);
    SetCursorPos(4, 2);
    DisableCursor();
    SetTextColor(FG_LIGHTRED | BG_LIGHTBLUE);
    puts("Kernel panic\n\n\t");
    SetTextColor(FG_WHITE | BG_LIGHTBLUE);
    printf("Exception number: %u\n\n\t", intNb);
    printf("Error: %s\n\t", errorText);
    printf("Error code: %u\n\t", errorCode);
    Halt();
}

char* errorTexts[32] = 
{
    "DIVISION_ERROR",
    "DEBUG",
    "NON-MASKABLE_INTERRUPT",
    "BREAKPOINT",
    "OVERFLOW",
    "BOUND_RANGE_EXCEEDED",
    "INVALID_OPCODE",
    "DEVICE_NOT_AVAILABLE",
    "DOUBLE_FAULT",
    "COPROCESSOR_SEGMENT_OVERRUN",
    "INVALID_TSS",
    "SEGMENT_NOT_PRESENT",
    "STACK_SEGMENT_FAULT",
    "GENERAL_PROTECTION_FAULT",
    "PAGE_FAULT",
    "",
    "X87_FLOATING_POINT_EXCEPTION",
    "ALIGNMENT_CHECK",
    "MACHINE_CHECK",
    "SIMD_FLOATING_POINT_EXCEPTION",
    "VIRTUALIZATION_EXCEPTION",
    "CONTROL_PROTECTION_EXCEPTION",
    "",
    "",
    "",
    "",
    "",
    "",
    "HYPERVISOR_INJECTION_EXCEPTION",
    "VMM_COMMUNICATION_EXCEPTION",
    "SECURITY_EXCEPTION",
    ""
};

void InterruptHandler(struct Registers* registers)
{
    if(registers->interruptNumber < 32)
    {
        kpanic(registers->interruptNumber, registers->errorCode, errorTexts[registers->interruptNumber]);
        while(true);
    }
    else if(registers->interruptNumber < 32 + 16)
    {
        uint8_t irqNumber = registers->interruptNumber - 32;
        if(irqNumber == 7 && !(PICGetISR() >> 7))
            return;
        if(irqNumber == 15 && !(PICGetISR() >> 15))
        {
            outb(PIC1_CMD, PIC_EOI);
	        io_wait();
            return;
        }
        switch (irqNumber)
        {
        case 0:
            TimerHandler();
            break;

        case 1:
            PS2KeyboardHandler();
            break;

        default:
            break;
        }
        PICSendEOI(irqNumber);
    }
}

extern void ISR0();
extern void ISR1();
extern void ISR2();
extern void ISR3();
extern void ISR4();
extern void ISR5();
extern void ISR6();
extern void ISR7();
extern void ISR8();
extern void ISR9();
extern void ISR10();
extern void ISR11();
extern void ISR12();
extern void ISR13();
extern void ISR14();
extern void ISR15();
extern void ISR16();
extern void ISR17();
extern void ISR18();
extern void ISR19();
extern void ISR20();
extern void ISR21();
extern void ISR22();
extern void ISR23();
extern void ISR24();
extern void ISR25();
extern void ISR26();
extern void ISR27();
extern void ISR28();
extern void ISR29();
extern void ISR30();
extern void ISR31();

extern void IRQ0();
extern void IRQ1();
extern void IRQ2();
extern void IRQ3();
extern void IRQ4();
extern void IRQ5();
extern void IRQ6();
extern void IRQ7();
extern void IRQ8();
extern void IRQ9();
extern void IRQ10();
extern void IRQ11();
extern void IRQ12();
extern void IRQ13();
extern void IRQ14();
extern void IRQ15();

void SetUpIDT()
{
    _idtr.base = (uint32_t)&idt;
    _idtr.limit = sizeof(struct IDTEntry) * 256 - 1;

    memset(&idt, 0, sizeof(struct IDTEntry) * 256);

    CreateIDTEntry(0, (uint32_t)&ISR0, 0x08, 0x8e);
    CreateIDTEntry(1, (uint32_t)&ISR1, 0x08, 0x8e);
    CreateIDTEntry(2, (uint32_t)&ISR2, 0x08, 0x8e);
    CreateIDTEntry(3, (uint32_t)&ISR3, 0x08, 0x8e);
    CreateIDTEntry(4, (uint32_t)&ISR4, 0x08, 0x8e);
    CreateIDTEntry(5, (uint32_t)&ISR5, 0x08, 0x8e);
    CreateIDTEntry(6, (uint32_t)&ISR6, 0x08, 0x8e);
    CreateIDTEntry(7, (uint32_t)&ISR7, 0x08, 0x8e);
    CreateIDTEntry(8, (uint32_t)&ISR8, 0x08, 0x8e);
    CreateIDTEntry(9, (uint32_t)&ISR9, 0x08, 0x8e);
    CreateIDTEntry(10, (uint32_t)&ISR10, 0x08, 0x8e);
    CreateIDTEntry(11, (uint32_t)&ISR11, 0x08, 0x8e);
    CreateIDTEntry(12, (uint32_t)&ISR12, 0x08, 0x8e);
    CreateIDTEntry(13, (uint32_t)&ISR13, 0x08, 0x8e);
    CreateIDTEntry(14, (uint32_t)&ISR14, 0x08, 0x8e);
    CreateIDTEntry(15, (uint32_t)&ISR15, 0x08, 0x8e);
    CreateIDTEntry(16, (uint32_t)&ISR16, 0x08, 0x8e);
    CreateIDTEntry(17, (uint32_t)&ISR17, 0x08, 0x8e);
    CreateIDTEntry(18, (uint32_t)&ISR18, 0x08, 0x8e);
    CreateIDTEntry(19, (uint32_t)&ISR19, 0x08, 0x8e);
    CreateIDTEntry(20, (uint32_t)&ISR20, 0x08, 0x8e);
    CreateIDTEntry(21, (uint32_t)&ISR21, 0x08, 0x8e);
    CreateIDTEntry(22, (uint32_t)&ISR22, 0x08, 0x8e);
    CreateIDTEntry(23, (uint32_t)&ISR23, 0x08, 0x8e);
    CreateIDTEntry(24, (uint32_t)&ISR24, 0x08, 0x8e);
    CreateIDTEntry(25, (uint32_t)&ISR25, 0x08, 0x8e);
    CreateIDTEntry(26, (uint32_t)&ISR26, 0x08, 0x8e);
    CreateIDTEntry(27, (uint32_t)&ISR27, 0x08, 0x8e);
    CreateIDTEntry(28, (uint32_t)&ISR28, 0x08, 0x8e);
    CreateIDTEntry(29, (uint32_t)&ISR29, 0x08, 0x8e);
    CreateIDTEntry(30, (uint32_t)&ISR30, 0x08, 0x8e);
    CreateIDTEntry(31, (uint32_t)&ISR31, 0x08, 0x8e);

    CreateIDTEntry(32, (uint32_t)&IRQ0, 0x08, 0x8e);
	CreateIDTEntry(33, (uint32_t)&IRQ1, 0x08, 0x8e);
	CreateIDTEntry(34, (uint32_t)&IRQ2, 0x08, 0x8e);
	CreateIDTEntry(35, (uint32_t)&IRQ3, 0x08, 0x8e);
	CreateIDTEntry(36, (uint32_t)&IRQ4, 0x08, 0x8e);
	CreateIDTEntry(37, (uint32_t)&IRQ5, 0x08, 0x8e);
	CreateIDTEntry(38, (uint32_t)&IRQ6, 0x08, 0x8e);
	CreateIDTEntry(39, (uint32_t)&IRQ7, 0x08, 0x8e);
	CreateIDTEntry(40, (uint32_t)&IRQ8, 0x08, 0x8e);
	CreateIDTEntry(41, (uint32_t)&IRQ9, 0x08, 0x8e);
	CreateIDTEntry(42, (uint32_t)&IRQ10, 0x08, 0x8e);
	CreateIDTEntry(43, (uint32_t)&IRQ11, 0x08, 0x8e);
	CreateIDTEntry(44, (uint32_t)&IRQ12, 0x08, 0x8e);
	CreateIDTEntry(45, (uint32_t)&IRQ13, 0x08, 0x8e);
	CreateIDTEntry(46, (uint32_t)&IRQ14, 0x08, 0x8e);
	CreateIDTEntry(47, (uint32_t)&IRQ15, 0x08, 0x8e);

    LoadIDT();
}