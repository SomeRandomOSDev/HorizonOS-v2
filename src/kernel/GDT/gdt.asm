gdtr:
    dw 0
    dd 0

global LoadGDT
; void LoadGDT(uint16_t limit, uint32_t base)
LoadGDT:
   mov   ax, [esp + 4]
   mov   [gdtr], ax
   mov   eax, [esp + 8]
   mov   [gdtr + 2], eax
   lgdt  [gdtr]
   ret