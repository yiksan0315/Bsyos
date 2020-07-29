all:hello.o

hello.o:hello.c
	x86_64-linux-gnu-gcc $< -o $@ -c -m64 -ffreestanding  

clean:
	rm -f hello.o
