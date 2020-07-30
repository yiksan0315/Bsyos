OBJCOPY=x86_64-linux-gnu-objcopy -j .text -j .data -j .rodata -j .bss -S -O binary
LD64=x86_64-linux-gnu-ld -melf_x86_64 -nostdlib -T linker.ld -e main #_start
RESIZEIMAGE=./Utility/ResizeImage

x86_64=arch/x86_64

Ker=kernel
Uti=Utility

KEROBJ=$(Ker)/*.o

all: Sios.iso
	
# *** Archietcture ***
x86_64: Uti
	make -C $(x86_64)
#	make -C $(Ker)
	$(LD64) -o kernel.bin $(x86_64)/$(KEROBJ) #$(KEROBJ) 
	$(OBJCOPY) kernel.bin kernel.bin
	$(RESIZEIMAGE) kernel.bin

	mv $(x86_64)/boot/grub_boot/loader.bin .
	$(RESIZEIMAGE) loader.bin

Sios.iso: kernel.bin loader.bin
	grub-file --is-x86-multiboot loader.bin
	cp $^ isodir/boot
	grub-mkrescue -o $@ isodir

Uti: 
	make -C Utility

clean:
	make -C $(Ker) clean
	make -C $(x86_64) clean
	make -C $(Uti) clean
	rm -f Sios.iso
	rm -f isodir/boot/kernel.bin
	rm -f isodir/boot/loader.bin
	rm -f kernel.bin
	rm -f loader.bin
