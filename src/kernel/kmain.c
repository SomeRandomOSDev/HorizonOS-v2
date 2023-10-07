#include "util/defs.h"
#include "util/io.h"
#include "util/memory.h"
#include "util/string.h"
#include "util/textio.c"
#include "util/multiboot.h"

#include "core/gdt.h"
#include "core/idt.h"

int kmain();

void kernel(struct multiboot_info* multibootInfo, uint32_t magicNumber)
{
    SetUpGDT();
    SetUpIDT();
    EnableInterrupts();
    InitMemory();
    kmain();
}

int kmain()
{
    return 0;
}