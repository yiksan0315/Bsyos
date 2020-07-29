NASM=nasm -f elf64
CC=x86_64-linux-gnu-gcc -c -m64 -ffreestanding -masm=intel
#LD=x86_64-linux-gnu-ld -melf_x86_64 -e main -Ttext 0x200000 -nostdlib -T linker.x
#OBJCOPY=x86_64-linux-gnu-objcopy -j .text -j .data -j .rodata -j .bss -S -O binary
#RESIZEIMAGE=../Utility/ResizeImage.out

SRC=Source

COBJECT=$(notdir $(patsubst %.c,%.o,$(wildcard $(SRC)/*.c)))
ASMOBJECT=$(notdir $(patsubst %.S,%.o,$(wildcard $(SRC)/*.S)))

all:kernel
	
kernel:
	%.o:$(SOURCEDIR)/%.c
		$(CC) -o $@ $< 

	%.o:$(SOURCEDIR)/%.S
		$(NASM) -o $@ $<
	
clean:
	rm -f $(SRC)/*.o
