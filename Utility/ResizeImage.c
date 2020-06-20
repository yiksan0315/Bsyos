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
	
	int FileSz,i,iSize;
	FILE* ReszFp,*ImgFp;
	
	ReszFp=fopen(argv[1],"rb"); ImgFp=fopen("Temp/ResizeImage.img","wb"); 
	if(ReszFp==NULL)
	{
		printf("error:Couldn't find file:%s\n",argv[1]);
		exit(-1);
	}  
	if(ImgFp==NULL)
	{
		printf("error:Couldn't Open the File:ResizeImage.img\n");
		exit(-1);
	}
	
	fseek(ReszFp,0l,SEEK_END);
	iSize=ftell(ReszFp);	FileSz=512-ftell(ReszFp)%512;
	for(i=0; i<FileSz; i++)
		fputc(0x00,ImgFp);
	
	if(fclose(ReszFp)==EOF)
	{
		printf("error:Fail close File Stream:%s\n",argv[1]);
		exit(-1);
	}
	if(fclose(ImgFp)==EOF)
	{
		printf("error:Fail close File Stream:ResizeImage.img\n");
		exit(-1);
	}
	
	printf("ReSize File:[%s] Successfully!\nResized File Size:%dbyte\n",argv[1],iSize+FileSz);
	return 0;
}

