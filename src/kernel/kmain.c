#define PIT_FREQUENCY       100

#include "includes.h"

int kmain();

void kernel(struct multiboot_info* multibootInfo, uint32_t magicNumber)
{
    SetTextColor(BG_BLACK | FG_WHITE);
    SetUpGDT();
    SetUpIDT();
    InitPIC();
    PITSetFrequency(PIT_FREQUENCY);
    EnableInterrupts();
    InitMemory();
    int returnCode = kmain();
    printf("\nkmain stoped with return code %i", returnCode);
}

int kmain()
{   
    while(true);
    return 0;
}