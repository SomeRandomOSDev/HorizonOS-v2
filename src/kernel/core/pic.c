#pragma once

#include "pic.h"

void InitPIC()
{
	PICRemap();
}

void PICRemap()
{
    outb(PIC1_CMD, 0x11);
    outb(PIC2_CMD, 0x11);
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    outb(PIC1_DATA, 0x0);
    outb(PIC2_DATA, 0x0);
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