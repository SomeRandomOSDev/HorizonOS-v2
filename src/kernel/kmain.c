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
    SetTextColor(FG_WHITE | BG_BLACK);
    char* string = (char*)malloc(11 * sizeof(char));
    char* string2 = "stringabc\n";
    char* string3 = (char*)malloc(5 * sizeof(char));
    string3[0] = 'm';
    string3[1] = 'a';
    string3[2] = 'l';
    string3[3] = '\n';
    string3[4] = '\0';
    memcpy(string, string2, 11);
    puts(string);
    puts(string3);

    uint8_t* array = (uint8_t*)malloc(1024 * sizeof(uint8_t));
    uint8_t* array2 = (uint8_t*)malloc(4096 * sizeof(uint8_t));

    free(array);
    free(string);
    
    //int x = 1 / 0;

    printMemState(0x00000000);

    return 0;
}