ENTRY(_start)
STARTUP("bin/kernelentry.o")

INPUT
(
 	"bin/kmain.o"
	"bin/idt.o"
	"bin/paging.o"
)
 
SECTIONS
{
	. = 1M;
 
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
 
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
 
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}