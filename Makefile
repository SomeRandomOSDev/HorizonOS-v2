bin/kernel.bin: src/kernel/kernelentry.asm clean
	echo Building HorizonOS...
	echo
	nasm -f elf -o "bin/kernelentry.o" "src/kernel/kernelentry.asm"
	gcc -Wall -m32 -ffreestanding -fstrength-reduce\
    -finline-functions -fno-pic \
    -mno-red-zone -masm=intel -std=gnu99 -nostdlib -c \
    -static -fno-common -fno-exceptions  \
    -fno-non-call-exceptions -fno-builtin "src/kernel/kmain.c" -o "bin/kmain.o"
	ld -m elf_i386 -T link.ld "bin/kernelentry.o" "bin/kmain.o" -o "bin/kernel.bin"
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