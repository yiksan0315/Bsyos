Boot=Bootstrap
Ker_32=kernel_32bit
Ker_64=kernel_64bit
Uti=Utility

all:Uti Ker_32 Ker_64 Sios.iso

Ker_32:
	make -C kernel_32bit
Ker_64:
	make -C kernel_64bit

Sios.iso: $(Ker_32)/kernel_32.img #$(Ker_64)/kernel_64.img 
	grub-file --is-x86-multiboot $<
	cp $< isodir/boot
	grub-mkrescue -o $@ isodir

Uti: 
	make -C Utility

clean:
	make -C $(Ker_32) clean
#	make -C $(Ker_64) clean
	rm -f Sios.iso
	rm -f isodir/boot/kernel_32.img
