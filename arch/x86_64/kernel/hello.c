#define VIDEO 0xB8000
#define VIDEO_GREEN 0x0A
#define I i*2

void printk(const char* Message);

void main(void){
	printk("Hello!!!");
}

void printk(const char* Message){
	int i;
	char *cVideo=(char *)VIDEO;

	for(i=0; Message[i]!='\0'; i++){
		cVideo[I]=Message[i];
		cVideo[I+1]=VIDEO_GREEN;
	}
}
