#include "includes.h"

int kmain();

void kernel(struct multiboot_info* multibootInfo, uint32_t magicNumber)
{
    SetTextColor(BG_BLACK | FG_WHITE);

    InitMemory();    

    printf("Initializing paging...\n");
    InitPageDirectory();

    printf("Setting up the GDT...\n");
    SetUpGDT();
    printf("Setting up the IDT...\n");
    SetUpIDT();
    printf("Initializing the PIC and the IRQs...\n\n");
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
    printf("Enter anything : ");
    char* string = PS2KeyboardReadTextInput();
    printf("You typed : %s\n", string);
    free(string);

    // for(uint32_t i = 0; i < 25; i++)
    //     printf("random number : %i\n", PRNGLFSR());
    
    while(true)
    {
        if(PS2KBGetKeyState(KB_LCTRL) && PS2KBGetKeyState('d'))
            memDump((void*)FREE_MEMORY_START);
        //free(PS2KeyboardReadTextInput());
    }
    return 0;
}