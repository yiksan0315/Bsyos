#include <debug.h>
#define VIDEO 0xB8000
#define WIDTH 80*2

void Debug(unsigned int _arg)
{
	static char *Video=(char *)VIDEO;
	while(_arg)	
	{
		*Video=_arg%10+'0';
		*(Video+1)=0x0A;
		_arg=_arg/10;
		Video=Video+2;
	}
	*Video=' ';
	*(Video+1)=0x0A;
	Video=Video+2;
}

void Debug_str(const char* _arg)
{
	int i;
	char *Video=(char *)(VIDEO+WIDTH*4);

	for(i=0; _arg[i]!='\0'; i++){
		*Video=_arg[i];
		*(Video+1)=0x0B;
		Video=Video+2;
	}	
}
