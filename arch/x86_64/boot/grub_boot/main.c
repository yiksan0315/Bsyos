#include <multiboot.h>
#include <debug.h>
#include <paging.h>

extern int Switch_IA_32e_Mode(void *IA_32eE);

void main(uint32_t magic_value,const void* multiboot_struct){
 
	if(magic_value != MULTIBOOT_BOOTLOADER_MAGIC){
		return;
	}
    const multiboot_info_t* mb_info = multiboot_struct;         /* Make pointer to multiboot_info_t struct */
	multiboot_uint32_t mb_flags = mb_info->flags;               /* Get flags from mb_info */
 
    void* kentry = NULL;                                        /* Pointer to the kernel entry point */
 
    if (mb_flags & MULTIBOOT_INFO_MODS) {                       /* Check if modules are available */
        multiboot_uint32_t mods_count = mb_info->mods_count;	/* Get the amount of modules available */
		multiboot_uint32_t mods_addr = mb_info->mods_addr;		/* And the starting address of the modules */

		multiboot_module_t* module = (multiboot_module_t*)mods_addr;     
	
		kentry = (multiboot_uint32_t*) module->mod_start;       
	}

	MakePageTable();
	Switch_IA_32e_Mode(kentry);
}
