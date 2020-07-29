#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	if(argc>=3)
	{
		printf("error:Too many Argument\n");
		exit(-1);
	}
	if(argc==1)
	{
		printf("error:No Input File\n");
		exit(-1);
	}
	
	int i;
	unsigned int iNeedFileSz,iSize;
	FILE* ReszFp;
	
	ReszFp=fopen(argv[1],"ab"); 
	if(ReszFp==NULL)
	{
		printf("error:Couldn't find file:%s\n",argv[1]);
		exit(-1);
	}  
	
	fseek(ReszFp,0l,SEEK_END);
	iSize=ftell(ReszFp);	iNeedFileSz=512-ftell(ReszFp)%512;
	for(i=0; i<iNeedFileSz; i++)
		fputc(0x00,ReszFp);
	
	if(fclose(ReszFp)==EOF)
	{
		printf("error:Fail close File Stream:%s\n",argv[1]);
		exit(-1);
	}
	
	printf("ReSize File:[%s] Successfully!\n",argv[1]);
	printf("Resized File Size:%dbyte\n",iSize+iNeedFileSz);
	return 0;
}

