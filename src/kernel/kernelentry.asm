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

; section .bss
section .data
; align 16
times 16384 db 0
stack_top: