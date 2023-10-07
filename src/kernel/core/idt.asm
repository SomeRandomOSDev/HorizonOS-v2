%macro ISR_ERROR_CODE 1
global ISR%1
ISR%1:
    cli
    push byte %1
    jmp GeneralInterruptHandler
%endmacro
%macro ISR_NO_ERROR_CODE 1
global ISR%1
ISR%1:
    cli
    push byte 0
    push byte %1
    jmp GeneralInterruptHandler
%endmacro

ISR_NO_ERROR_CODE 0
ISR_NO_ERROR_CODE 1
ISR_NO_ERROR_CODE 2
ISR_NO_ERROR_CODE 3
ISR_NO_ERROR_CODE 4
ISR_NO_ERROR_CODE 5
ISR_NO_ERROR_CODE 6
ISR_NO_ERROR_CODE 7
ISR_ERROR_CODE    8
ISR_NO_ERROR_CODE 9
ISR_ERROR_CODE    10
ISR_ERROR_CODE    11
ISR_ERROR_CODE    12
ISR_ERROR_CODE    13
ISR_ERROR_CODE    14
ISR_NO_ERROR_CODE 15
ISR_NO_ERROR_CODE 16
ISR_ERROR_CODE    17
ISR_NO_ERROR_CODE 18
ISR_NO_ERROR_CODE 19
ISR_NO_ERROR_CODE 20
ISR_NO_ERROR_CODE 21
ISR_NO_ERROR_CODE 22
ISR_NO_ERROR_CODE 23
ISR_NO_ERROR_CODE 24
ISR_NO_ERROR_CODE 25
ISR_NO_ERROR_CODE 26
ISR_NO_ERROR_CODE 27
ISR_NO_ERROR_CODE 28
ISR_NO_ERROR_CODE 29
ISR_ERROR_CODE    30
ISR_NO_ERROR_CODE 31

%macro IRQ_HANDLER 1
global IRQ%1
IRQ%1:
    cli
    push byte 0
    push byte (%1 + 32)
    jmp GeneralInterruptHandler
%endmacro

IRQ_HANDLER 0
IRQ_HANDLER 1
IRQ_HANDLER 2
IRQ_HANDLER 3
IRQ_HANDLER 4
IRQ_HANDLER 5
IRQ_HANDLER 6
IRQ_HANDLER 7
IRQ_HANDLER 8
IRQ_HANDLER 9
IRQ_HANDLER 10
IRQ_HANDLER 11
IRQ_HANDLER 12
IRQ_HANDLER 13
IRQ_HANDLER 14
IRQ_HANDLER 15

extern InterruptHandler
GeneralInterruptHandler:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, InterruptHandler
    call eax 
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8 
    iret 
