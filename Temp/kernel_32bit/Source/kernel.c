#include "tty.h"

BOOL Check_Memory(void);
BOOL Init_IA32e(void);

void _CPUID(u32 arg_EAX,u32* ret_EAX,u32* EBX,u32* ECX,u32* EDX);
void Switch_IA_32e_Mode();
void kCopyKernel64ImageTo2Mbyte( void );

void Debug(int Number);

void main()
{ 
	char CpuMessage[22]={"Cpu is:["};
	u32 arg_ERgst[4];
	printk("Check Memory size...",7,_WHITE);
	if(!Check_Memory())
	{
		printk("Not Enough Memory... Memory is at least 128MB",8,_RED);
		return ;
	}
	printk("Memory Size is Enough!",8,_BLUE);
	
	printk("Initializing IA-32e Kernel Area...",9,_WHITE);

	if(!Init_IA32e()) 
	{
		printk("Error:Can't Initializing IA-32e Kernel Area...",10,_RED);
		return ;
	}
	printk("Initializing IA-32e Kernel Area Successfully!",10,_BLUE);
	_CPUID(0,&arg_ERgst[0],&arg_ERgst[1],&arg_ERgst[2],&arg_ERgst[3]);
	
	*((u32*)CpuMessage+2)=arg_ERgst[1]; *((u32*)CpuMessage+3)=arg_ERgst[3]; *((u32*)CpuMessage+4)=arg_ERgst[2];
	CpuMessage[20]=']'; CpuMessage[21]='\0';
	printk(CpuMessage,12,CYAN);
	
	_CPUID(0x80000001,&arg_ERgst[0],&arg_ERgst[1],&arg_ERgst[2],&arg_ERgst[3]);
	if(arg_ERgst[3]&0x20000000) //0010 0000 0000 0000 0000 0000 0000 0000
	{
		printk("This Cpu Supports IA-32e Mode!",13,_BLUE);
	}
	else
	{
		printk("This Cpu doesn't Support IA-32e Mode! ... Can't Switch kernel to IA-32e Mode",13,_RED);
		return ;
	}
	printk("Switch to IA-32e Mode...",15,_WHITE);
//	kCopyKernel64ImageTo2Mbyte();
	Switch_IA_32e_Mode();
    return ;
}

void Debug(int Number){
	char* Video=(char*)0xB8000+(20*80)*2;
	char Array[100];
	int Count=0;
	while(Number>=10)
	{
		Array[Count]=Number%10;
		Number/=10;
		Count++;
	}
	Array[Count]=Number%10;

	while(Count>=0)
	{
		*Video=Array[Count--]+48;
		Video++;
		*Video=0x0A;
		Video++;
	}
}
BOOL Check_Memory(void)
{
	u32* NowAddress;
	for(NowAddress=(u32 *)0x100000; NowAddress<=(u32 *)0x8000000; NowAddress+=(0x100000/4))
	{
		*NowAddress=0x12345678;
		if(*NowAddress!=0x12345678)
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL Init_IA32e(void)
{
	u32* NowAddress;
	printk("what?",2,_CYAN);
	for(NowAddress=(u32 *)0x112A02; NowAddress<=(u32 *)0x600000; NowAddress++)
	{
		Debug((int)NowAddress);
		*NowAddress=0x00;
		if(*NowAddress!=0x00)
			return FALSE;
	}
	return TRUE;
}

/*void kCopyKernel64ImageTo2Mbyte( void )
{
    unsigned short wKernel32SectorCount, wTotalKernelSectorCount;
    u32* pdwSourceAddress,* pdwDestinationAddress;

    int i;
    wTotalKernelSectorCount = *( (unsigned short* ) 0x7D4A );
    wKernel32SectorCount = *( ( unsigned short* ) 0x7D48 );
    pdwSourceAddress = ( u32* ) ( 0x10000 + ( wKernel32SectorCount * 512 ) );

    pdwDestinationAddress = ( u32* ) 0x200000;

    // IA-32e ��� Ŀ�� ���� ũ�⸸ŭ ����

    for( i = 0 ; i < 512 * ( wTotalKernelSectorCount - wKernel32SectorCount ) / 4; i++ )
    {
        *pdwDestinationAddress = *pdwSourceAddress;
        pdwDestinationAddress++;
        pdwSourceAddress++;
    }
}
*/
