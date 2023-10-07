ALIGNMENT equ 1
MEMINFO equ  (1 << 1)   
FLAGS equ (ALIGNMENT | MEMINFO)
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

section .text

[extern kernel]
global _start
_start:
[bits 32]
	push eax
	push ebx

	call kernel

	cli
  	hlt
	jmp $

global LoadGDT
extern gdtPtr
; void LoadGDT()
LoadGDT:
    lgdt  [gdtPtr]
    jmp 0x08:.reloadCS
.reloadCS:
	mov   ax, 0x10
    mov   ds, ax
    mov   es, ax
    mov   fs, ax
    mov   gs, ax
    mov   ss, ax

    ret

global LoadIDT
extern _idtr
; void LoadIDT()
LoadIDT:
    lidt [_idtr]
    ret

; section .bss
section .data
; align 16
times 16384 db 0
stack_top: