bin/kernel.bin: src/kernel/kernelentry.asm clean
	echo Building HorizonOS...
	echo
	nasm -f elf -o "bin/kernelentry.o" "src/kernel/kernelentry.asm"
	nasm -f elf -o "bin/idt.o" "src/kernel/core/idt.asm"
	nasm -f elf -o "bin/paging.o" "src/kernel/core/paging.asm"
	gcc -c "src/kernel/kmain.c" -o "bin/kmain.o" -std=gnu99 -ffreestanding -Wall -masm=intel -m32
	ld -m elf_i386 -T link.ld -o "bin/kernel.bin"
	mkdir -p iso/boot/grub
	cp bin/kernel.bin iso/boot/kernel.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o horizonos.iso iso

run:
	qemu-system-i386 -cdrom "horizonos.iso"

debug:
	bochs -f bochsrc

clean:
	rm -rf bin/*
	rm -rf iso