bin/horizonos.bin: Makefile bin/kernel.bin
	echo Building HorizonOS...
	echo
	# dd if="/dev/zero" of="bin/horizonos.bin" bs=512 count=2880
	# mkfs.fat -F 12 -n "HORIZONOS" "bin/horizonos.bin"
	# mcopy -i "bin/horizonos.bin" "bin/kernel.bin" "::kernel.bin"
	# dd if="bin/boot.bin" of="bin/horizonos.bin" conv=notrunc
	mkdir -p iso/boot/grub
	cp bin/kernel.bin iso/boot/kernel.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o horizonos.iso iso

bin/kernel.bin: src/kernel/kernelentry.asm
	nasm -f elf -o "bin/kernel.o" "src/kernel/kernelentry.asm"
	ld -m elf_i386 -T link.ld -o "bin/kernel.bin" "bin/kernel.o"

run:
	qemu-system-i386 -cdrom "horizonos.iso"

debug:
	bochs -f bochsrc

clean:
	rm -rf bin/*
	rm -rf iso