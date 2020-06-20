NASM=nasm
CC=x86_64-linux-gnu-gcc -c -m32 -MD -Wall -Wextra -ffreestanding
LD=x86_64-linux-gnu-ld -melf_i386 -e _start -nostdlib -T linker.ld
OBJCOPY=x86_64-linux-gnu-objcopy -j .text -j .data -j .rodata -j .bss -S -O binary
RESIZEIMAGE=../Utility/ResizeImage.out

TEMPDIR=Temp
SOURCEDIR=Source

all:kernel_32.img #$(TEMPDIR)/GDT.img 

#	$(OBJCOPY) $^ $(TEMPDIR)/Tempimg.img
#	cat $(TEMPDIR)/GDT.img $(TEMPDIR)/Tempimg.img> $@

kernel_32.img:$(TEMPDIR)/Boot.o $(TEMPDIR)/kernel.o $(TEMPDIR)/IO.o $(TEMPDIR)/paging.o $(TEMPDIR)/Entry_64bit.o 
	$(LD) -o $@ $^
	$(RESIZEIMAGE) $@

$(TEMPDIR)/paging.o:$(SOURCEDIR)/paging.c
	$(CC) -o $@ $^

$(TEMPDIR)/kernel.o:$(SOURCEDIR)/kernel.c
	$(CC) -o $@ $^

$(TEMPDIR)/IO.o:$(SOURCEDIR)/IO.c
	$(CC) -o $@ $^

$(TEMPDIR)/Entry_64bit.o:$(SOURCEDIR)/Entry_64bit.asm
	$(NASM) -f elf -o $@ $^

#$(TEMPDIR)/GDT.img:$(SOURCEDIR)/GDT.asm
#	$(NASM) -f bin -o $@ $^

$(TEMPDIR)/Boot.o:$(SOURCEDIR)/Boot.S
	$(CC) -o $@ $^

clean:
	rm -f *.img
	rm -f $(TEMPDIR)/*.*


