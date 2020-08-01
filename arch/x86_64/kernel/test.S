extern main

_start:
    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    mov rsp,0x6FFFF8
    mov rbp,0x6FFFF8

	mov rbx,0xB8000
	mov byte[rbx],'Q'
	inc rbx
	mov	byte[rbx],0x51


	call main

jmp $
