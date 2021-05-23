objects = boot.o kernel.o console.o

kernel.elf: $(objects)
	ld -m elf_i386 -e entry -Ttext 0x100000 $(objects) -o $@
	objdump -S $@ > kernel.asm

%.o: %.c
	cc -m32 -ffreestanding -c $<

%.o: %.S
	cc -m32 -c $<

run: kernel.elf
	DISPLAY=:0 qemu-system-i386 -m 64M -kernel kernel.elf -monitor stdio

clean:
	rm -f *.elf *.o *.asm
