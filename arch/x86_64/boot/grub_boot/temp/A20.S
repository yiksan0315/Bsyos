A20_set:
	_BIOSint:
		mov ax,0x2401
		int 0x15
		jc _SysCtrlPort
		mov byte[IsOnA20],1
		jmp _RealMode

	_SysCtrlPort:
		in al,0x92
		or al,0x2
		and al,0xFE
		out 0x92,al

		call CheckA20
		cmp byte[IsOnA20],0
		jz _KeyBoardController
		jmp _RealMode

	_KeyBoardController:
		cli

		call CheckInput
		mov al,0xAD
		out 0x64,al

		call CheckInput
		mov al,0xD0
		out 0x64,al

		call CheckOutput
		in al,0x60
		push ax

		call CheckInput
		mov al,0xD1
		out 0x64,al

		call CheckInput
		pop ax
		or al,2
		out 0x60,al

		call CheckInput
		mov al,0xAE
		out 0x64,al

		sti
		call CheckA20
		jmp _RealMode

		CheckInput:
			in al,0x64
			test al,2
			jnz CheckInput
			ret
		CheckOutput:
			in al,0x64
			test al,1
			jz CheckOutput
			ret

	CheckA20:
		push es
		push ax
		push si

		mov ax,0x0
		mov es,ax
		mov si,0x500
		mov word[es:si],0x0000

		mov ax,0xFFFF
		mov es,ax
		mov si,0x510
		mov word[es:si],0x0000

		mov ax,0xFFFF
		mov word[es:si],ax

		mov ax,0x0
		mov es,ax
		mov si,0x500

		mov ax,word[es:si]
		cmp ax,0xFFFF
		jz _NotOnA20

		_OnA20:
			pop si
			pop ax
			pop es
			mov byte[IsOnA20],1
		ret
		_NotOnA20:
			pop si
			pop ax
			pop es
			mov byte[IsOnA20],0
		ret

db IsOnA20 0
