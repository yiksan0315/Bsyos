#include <multiboot.h>
#include <debug.h>
#include <paging.h>

extern int Switch_IA_32e_Mode(void *IA_32eE);
void Copy_to(void *Src, void *Des, uint32_t uSize);
void Init(void *Des, uint32_t uSize);

void main(uint32_t magic_value,const void* multiboot_struct){
 
	if(magic_value != MULTIBOOT_BOOTLOADER_MAGIC){
		return;
	}
    const multiboot_info_t* mb_info = multiboot_struct;         /* Make pointer to multiboot_info_t struct */
	multiboot_uint32_t mb_flags = mb_info->flags;               /* Get flags from mb_info */
 
    void* kentry = NULL;                                        /* Pointer to the kernel entry point */
	void* kentry_end = NULL;
 
    if (mb_flags & MULTIBOOT_INFO_MODS) {                       /* Check if modules are available */
        multiboot_uint32_t mods_count = mb_info->mods_count;	/* Get the amount of modules available */

		if(mods_count <= 0){
			return ;
		}

		multiboot_uint32_t mods_addr = mb_info->mods_addr;		/* And the starting address of the modules */

		multiboot_module_t* module = (multiboot_module_t*)mods_addr;     
	
		kentry = (multiboot_uint32_t *) module->mod_start;       
		kentry_end = (multiboot_uint32_t *) module->mod_end;       

		Copy_to(kentry, (void *)KER_64, (uint32_t)(kentry_end - kentry));
		Init(kentry, (uint32_t)(kentry_end - kentry));
	}
	else {
		return;
	}

	MakePageTable();
	Switch_IA_32e_Mode(kentry);
}

void Copy_to(void *Src, void *Des, uint32_t uSize) {
	uint32_t i=0;
	while(i < uSize){
		*((char *)Des + i) = *((char *)Src + i);
		i++;
	}
}

void Init(void *Des, uint32_t uSize) {
	uint32_t i=0;
	while(i < uSize) {
		*((char *)Des+i) = 0;
		i++;
	}
}
