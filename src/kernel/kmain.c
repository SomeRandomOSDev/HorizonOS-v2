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
    kmain();
}

int kmain()
{
    SetTextColor(FG_WHITE | BG_BLACK);
    puts("Hello world !");
    int x = 1 / 0;
    return 0;
}