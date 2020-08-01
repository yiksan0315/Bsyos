global _init_GDT

# Init Global Descriptor Tablei with 32bit descriptor
_init_GDT:
	push eax
	cli
	lgdt[GDTR]

	mov eax,0x4000003B
	mov cr0,eax

	jmp $+2
	nop
	nop

jmp dword descriptor_32_t_code:.init_gdt

.init_gdt:
    mov ax,descriptor_32_t_data
    mov es,ax
    mov ds,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax

	pop eax
	ret

GDTR:
    dw GDT_END-GDT-1
    dd GDT

align 8

GDT:
NullDescriptor equ 0x00
    dw 0x0 ; 세그먼트 크기
    dw 0x0 ; 기준 주소 16~31(16bit)
    db 0x0 ; 기준 주소 32~39(8bit)
    db 0x0 ; P(1bit), DPL(2bit), S(1bit) + type(4bit) = (8bit)
    db 0x0 ; G, D/B, L, AVL(4bit) + 세그먼트 크기 36~39(4bit)=(8bit)
    db 0x0 ; 기준 주소 63~56(8bit)
IA_32e_CodeDescriptor equ 0x08
    dw 0x0000
    dw 0x0000
    db 0x00
    db 0x9A ; 1001 1010 | P=1 | DPL=0 | S=1 (Code&Data Segment) | type=1010 (non-conforming,readable)
    db 0x20
    db 0x00
IA_32e_DataDescriptor equ 0x10
    dw 0x0000
    dw 0x0000
    db 0x00
    db 0x92 ; 1001 0010 | P=1 | DPL=0 | S=1 (Code&Data Segment) | type=0010 (read&Write)
    db 0x20
    db 0x00
descriptor_32_t_code equ 0x18
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0x9A ; 1001 1010 | P=1 | DPL=0 | S=1 (Code&Data Segment) | type=1010 (non-conforming,readable)
    db 0xCF ; 1100 1111 | G=1 | D/B=1 | L=0(32bit) | AVL=0 | Segment Size=0xFFFF*0xF=0xFFFFF,0xFFFFF*0xFFF(4KB=4096B)=0xFFFFFFF
    db 0x00
descriptor_32_t_data equ 0x20
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0x92 ; 1001 0010 | P=1 | DPL=0 | S=1 (Code&Data Segment) | type=0010 (read&Write)
    db 0xCF ; 1100 1111 | G=1 | D/B=1 | L=0(32bit) | AVL=0 | Segment Size=0xFFFF*0xF=0xFFFFF,0xFFFFF*0xFFF(4KB=4096B)=0xFFFFFFF
    db 0x00
GDT_END:
