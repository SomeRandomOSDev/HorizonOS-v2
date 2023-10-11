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
    //     if(PS2KBGetKeyState(KB_UP))
    //         puts("UP ARROW PRESSED !!!!!!!!!!!!!!\r");
    //     else
    //         puts("                                          \r");
    // }
    printf("Enter anything : ");
    char* string = PS2KeyboardReadTextInput();
    printf("You typed : %s\n", string);
    free(string);
    
    while(true)
    {
        if(PS2KBGetKeyState(KB_LCTRL) && PS2KBGetKeyState('d'))
            memDump(string);
    }
    return 0;
}