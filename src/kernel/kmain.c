#include "includes.h"

int kmain();

void kernel(struct multiboot_info* multibootInfo, uint32_t magicNumber)
{
    SetTextColor(BG_BLACK | FG_WHITE);
    InitMemory();
    printf("Setting up GDT...\n");
    SetUpGDT();
    printf("Setting up IDT...\n\n");
    SetUpIDT();
    InitPIC();
    PITSetFrequency(100);
    printf("Initializing keyboard...\n\n");
    kb_layout = KB_AZERTY;
    PS2KeyboardInit();
    PS2KBResetKeyboard();
    PS2KBSetScancodeSet(2);

    EnableInterrupts();

	printf("Scanning PCI Buses...\n\n");
	printf("\n%u devices found.\n\n", PCIScanBuses());

    int returnCode = kmain();
    printf("\nkmain stoped with return code %i", returnCode);
}

int kmain()
{   
    // printf("Enter anything : ");
    // char* string = PS2KeyboardReadTextInput();
    // printf("You typed : %s\n", string);
    // free(string);
    
    while(true)
    {
        if(PS2KBGetKeyState(KB_LCTRL) && PS2KBGetKeyState('d'))
            ;//memDump(string);
    }
    return 0;
}