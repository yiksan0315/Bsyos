NASM=nasm -f elf
CC=x86_64-linux-gnu-gcc -c -m32 -MD -Wall -Wextra -ffreestanding 
LD=x86_64-linux-gnu-ld -melf_i386 -e _start -nostdlib -T linker.ld
RESIZEIMAGE=../Utility/ResizeImage.out

TEMPDIR=Temp
SOURCEDIR=Source

all:kernel_32.img 

kernel_32.img:$(TEMPDIR)/Boot.o $(TEMPDIR)/GDT.o $(TEMPDIR)/kernel.o $(TEMPDIR)/tty.o $(TEMPDIR)/paging.o $(TEMPDIR)/Entry_64bit.o 
	$(LD) -o $@ $^
	$(RESIZEIMAGE) $@

$(TEMPDIR)/paging.o:$(SOURCEDIR)/paging.c
	$(CC) -o $@ $^

$(TEMPDIR)/kernel.o:$(SOURCEDIR)/kernel.c
	$(CC) -o $@ $^

$(TEMPDIR)/tty.o:$(SOURCEDIR)/tty.c
	$(CC) -o $@ $^

$(TEMPDIR)/Entry_64bit.o:$(SOURCEDIR)/Entry_64bit.S
	$(NASM) -o $@ $^

$(TEMPDIR)/GDT.o:$(SOURCEDIR)/GDT.S
	$(NASM) -o $@ $^

$(TEMPDIR)/Boot.o:$(SOURCEDIR)/Boot.S
	$(CC) -o $@ $^

clean:
	rm -f *.img
	rm -f $(TEMPDIR)/*.*


