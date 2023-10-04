#include "util/defs.h"
#include "util/io.h"
#include "util/memory.h"
#include "util/string.h"
#include "util/textio.c"
#include "util/multiboot.h"

#include "GDT/gdt.h"

int kmain();

void kernel(struct multiboot_info* multibootInfo, uint32_t magicNumber)
{
    SetUpGDT();
    kmain();
}

int kmain()
{
    SetTextColor(FG_WHITE | BG_BLACK);
    puts("Hello world !");
    return 0;
}