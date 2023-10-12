[bits 32]
section .text
global LoadPageDirectory
LoadPageDirectory:
    push ebp
    mov ebp, esp

    mov eax, [esp + 8]
    mov cr3, eax

    mov esp, ebp
    pop ebp
    ret

global EnablePaging
EnablePaging:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    ret

global DisablePaging
DisablePaging:
    mov eax, cr0
    and eax, ~(0x80000000)
    mov cr0, eax
    ret

global GetCR2
GetCR2:
    mov eax, cr2
    ret