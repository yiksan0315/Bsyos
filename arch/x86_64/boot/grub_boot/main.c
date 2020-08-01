#include "include/multiboot.h"
#include "include/debug.h"

extern int Switch_IA_32e_Mode(void *IA_32eE);
//void* load_elf_module(multiboot_uint32_t mod_start, multiboot_uint32_t mod_end) 

void main(uint32_t magic_value,const void* multiboot_struct){
 
    const multiboot_info_t* mb_info = multiboot_struct;         /* Make pointer to multiboot_info_t struct */
	multiboot_uint32_t mb_flags = mb_info->flags;               /* Get flags from mb_info */
 
    void* kentry = NULL;                                        /* Pointer to the kernel entry point */
 
    if (mb_flags & MULTIBOOT_INFO_MODS) {                       /* Check if modules are available */
        multiboot_uint32_t mods_count = mb_info->mods_count;	/* Get the amount of modules available */
		multiboot_uint32_t mods_addr = mb_info->mods_addr;		/* And the starting address of the modules */

		Debug(mods_count);
		Debug(mods_addr);

		multiboot_module_t* module = (multiboot_module_t*)mods_addr;     
		Debug_str((const char*)module->cmdline);
		Debug(module->mod_start);
		Debug(module->mod_end);
	
		kentry = (multiboot_uint32_t*) module->mod_start;//load_elf_module(module->mod_start, module->mod_end);
	}

	Debug(Switch_IA_32e_Mode(kentry));
	Debug((multiboot_uint32_t) kentry);
}


//  char* kernel_elf_space[sizeof(elf_file_data_t)];
//  elf_file_data_t* kernel_elf = (elf_file_data_t*) kernel_elf_space;                                          /* Pointer to elf file structure (remember there is no memory management yet) */

/*void* load_elf_module(multiboot_uint32_t mod_start, multiboot_uint32_t mod_end) 
{
	unsigned long err = parse_elf_executable((void*)mod_start, sizeof(elf_file_data_t), kernel_elf);    // Parses ELF file and returns an error code 
	if(err == 0){                                                                                       // No errors occurred while parsing the file 
			for(int i = 0; i < kernel_elf->numSegments; i++){
		elf_file_segment_t seg = kernel_elf->segments[i];                                   // Load all the program segments into memory 
																							//  if you want to do relocation you should do so here, 
		const void* src = (const void*) (mod_start + seg.foffset);                          //  though that would require some changes to parse_elf_executable 
		memcpy((void*) seg.address, src, seg.flength);
	}
			return (void*) kernel_elf->entryAddr;                                                       // Finally we can return the entry address 
	}
	return NULL;

}*/




