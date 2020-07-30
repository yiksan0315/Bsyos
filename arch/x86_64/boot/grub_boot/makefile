NASM32=nasm -f elf32
CC32=x86_64-linux-gnu-gcc -c -m32 -ffreestanding -z max-page-size=0x1000 -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -O2 -Wall -Wextra 
LD32=x86_64-linux-gnu-ld -melf_i386 -e _start -nostdlib  -T multiboot_ld.ld -Ttext 0x100000

BOOTOBJECT_S_intel=$(notdir $(patsubst %.S,%.o,$(wildcard *.S)))
BOOTOBJECT_S_at_t=$(notdir $(patsubst %.s,%.o,$(wildcard *.s)))
BOOTOBJECT_C=$(notdir $(patsubst %.c,%.o,$(wildcard *.c)))

all:loader.bin

loader.bin:$(BOOTOBJECT_C) $(BOOTOBJECT_S_at_t) $(BOOTOBJECT_S_intel)
	$(LD32) -o $@ $^

%.o:%.c
		$(CC32) -o $@ $< 

%.o:%.S
		$(NASM32) -o $@ $<
			
%.o:%.s
		$(CC32) -o $@ $<

clean:
	rm -f ./*.o
	rm -f loader.bin
