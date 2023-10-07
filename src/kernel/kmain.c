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
    SetTextColor(BG_BLACK | FG_WHITE);
    SetUpGDT();
    SetUpIDT();
    EnableInterrupts();
    InitMemory();
    int returnCode = kmain();
    printf("\nkmain stoped with return code %i", returnCode);
}

int kmain()
{
    printf("this is a formated string %i %s %u %c 0x%x 0x%X", -982, "arandomstring", 325, 'c', 0x89ab00, 0x0123abcd);
    return 0;
}