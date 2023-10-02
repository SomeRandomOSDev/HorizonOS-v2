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

section .bss
align 16
stack_bottom:

stack_top:

section .text
global _start
_start:
	; call kernel_main

	cli
  	hlt
	jmp $

; .size _start, . - _start ; .size _start, $ - _start ?