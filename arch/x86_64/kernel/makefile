all:test.o hello.o

hello.o:hello.c
	x86_64-linux-gnu-gcc $< -o $@ -c -m64 -ffreestanding  

test.o:test.S
	nasm -f elf64 $< -o $@ 

clean:
	rm -f hello.o
	rm -f test.o
