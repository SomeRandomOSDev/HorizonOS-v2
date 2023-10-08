#include "includes.h"

int kmain();

void kernel(struct multiboot_info* multibootInfo, uint32_t magicNumber)
{
    SetTextColor(BG_BLACK | FG_WHITE);
    SetUpGDT();
    SetUpIDT();
    InitPIC();
    PITSetFrequency(100);
    kb_layout = KB_AZERTY;
    PS2KeyboardInit();
    PS2KBResetKeyboard();
    PS2KBSetScancodeSet(2);
    EnableInterrupts();
    InitMemory();
    int returnCode = kmain();
    printf("\nkmain stoped with return code %i", returnCode);
}

int kmain()
{   
    // while(true)
    // {
    //     if(PS2KBGetKeyState('a'))
    //         puts("a\r");
    //     else
    //         puts(" \r");
    // }
    PS2KeyboardReadTextInput();
    return 0;
}