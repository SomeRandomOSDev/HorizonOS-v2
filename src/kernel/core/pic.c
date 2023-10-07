#pragma once

#include "pic.h"

void InitPIC()
{
    //PICRemap(32, 32 + 8);
	PICRemap();
	//PICSetMask(0xfffe);
}

// void PICRemap(int offset1, int offset2)
// {
// 	uint8_t a1, a2;
 
// 	a1 = inb(PIC1_DATA);
// 	io_wait();
// 	a2 = inb(PIC2_DATA);
 
// 	outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
// 	io_wait();
// 	outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);
// 	io_wait();
// 	outb(PIC1_DATA, offset1);
// 	io_wait();
// 	outb(PIC2_DATA, offset2);
// 	io_wait();
// 	outb(PIC1_DATA, 4);
// 	io_wait();
// 	outb(PIC2_DATA, 2);
// 	io_wait();
 
// 	outb(PIC1_DATA, ICW4_8086);
// 	io_wait();
// 	outb(PIC2_DATA, ICW4_8086);
// 	io_wait();
 
// 	outb(PIC1_DATA, a1);
// 	io_wait();
// 	outb(PIC2_DATA, a2);
// 	io_wait();
// }

void PICRemap()
{
    outb(0x20, 0x11);
    outb(0xa0, 0x11);
    outb(0x21, 0x20);
    outb(0xa1, 0x28);
    outb(0x21, 0x04);
    outb(0xa1, 0x02);
    outb(0x21, 0x01);
    outb(0xa1, 0x01);
    outb(0x21, 0x0);
    outb(0xa1, 0x0);
}

void PICDisable()
{
    outb(PIC2_DATA, 0xff);
	io_wait();
    outb(PIC1_DATA, 0xff);
	io_wait();
}

void PICSendEOI(uint8_t irq)
{
	if(irq >= 8)
		outb(PIC2_CMD, PIC_EOI);

	io_wait();
 
	outb(PIC1_CMD, PIC_EOI);

	io_wait();
}

void PICSetMask(uint16_t mask) 
{
    outb(PIC1_DATA, mask & 0xff);      
	io_wait();
	outb(PIC2_DATA, mask >> 8);      
	io_wait();
}

#define PIC_READ_IRR                0x0a
#define PIC_READ_ISR                0x0b
 
static uint16_t PICGetRegister(int32_t ocw3)
{
    outb(PIC1_CMD, ocw3);
    outb(PIC2_CMD, ocw3);
    return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}
 
uint16_t PICGetIRR()
{
    return PICGetRegister(PIC_READ_IRR);
}
 
uint16_t PICGetISR()
{
    return PICGetRegister(PIC_READ_ISR);
}