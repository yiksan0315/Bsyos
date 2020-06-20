# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

#	push %ebp 123123123123?
#	movl %esp,%ebp
	
	movl $0xB8000,%ebx
	movl $'H',(%ebx) 
	movl $0x07,1(%ebx) 

	movl $'E',2(%ebx) 
	movl $0x07,3(%ebx) 
	movl $'L',4(%ebx) 
	movl $0x07,5(%ebx) 
	movl $'L',6(%ebx) 
	movl $0x07,7(%ebx) 
	movl $'O',8(%ebx) 
	movl $0x07,9(%ebx) 

	call main
	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b

.size _start, . - _start
