global Switch_IA_32e_Mode

Switch_IA_32e_Mode:
	push	ebp
	mov	ebp, esp                ; Set up the stack so the variables passed from the C code can be read

    mov eax,cr4
    or eax,0x20
    mov cr4,eax

    mov eax,0x106000
    mov cr3,eax

    mov ecx,0xC0000080
    rdmsr
    or eax,0x0100
    wrmsr

    mov eax,cr0
    or eax,0xE0000000      
    xor eax,0x60000000  
    mov cr0,eax

	mov	esi, [ebp+8]            ; This is the kernel entry point
	mov	[k_ptr], esi
	
	jmp	0x08:0x200000; Reload code selector by jumping to 64-bit code

.jmp_k:
;	mov	edi, [ebp + 12]		; 1st argument of kernel_main (pointer to multiboot structure)
	mov	eax, [k_ptr]                                                                                                      ; This is transformed to mov rax, [k_ptr] and uses the double word reserved below 
	dd	0			; Trick the processor, contains high address of k_ptr                                     ; as higher half of the address to k_ptr
	jmp	eax                     
 
jmp $

section .data
k_ptr:
	dd	0
