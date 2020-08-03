extern main

_start:
;	lgdt[GDTR]
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

GDT64:                           ; Global Descriptor Table (64-bit).
    NullDescriptor equ 0x00				 ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).
    NullDescriptor2 equ 0x08				 ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0     
    NullDescriptor3 equ 0x10				 ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0     
    IA_32e_CodeDescriptor equ 0x18              ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    IA_32e_DataDescriptor equ 0x20			     ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).

GDTR:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64  
