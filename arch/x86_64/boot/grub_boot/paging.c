#include <paging.h>
#include <debug.h>

void MakePageTable(void){
	int i;
	page_uint_32t PageAddress = 0;
		PML4T* PML4_Table;
		PDPT*  PageDirPtr_Table;
		PDT*   PageDir_Table;
	
 	PML4_Table = (PML4T*) TABLE_ADR;
	PageDirPtr_Table=(PDPT*) (TABLE_ADR + PAGE_TABLE_SIZE);
	PageDir_Table=(PDT*) (TABLE_ADR + (PAGE_TABLE_SIZE * 2));

 	SetEntry(&PML4_Table[0], NUL, TABLE_ADR + PAGE_TABLE_SIZE, NONE, 0x3);
		for(i = 1; i < ENTRY_COUNT; i++)
			SetEntry(&PML4_Table[i], NUL, NUL, NONE, NONE);
	
	for(i = 0; i < 64; i++){
		SetEntry(&PageDirPtr_Table[i], NUL, (page_uint_32t)PageDirPtr_Table + 
				(i + 1) * PAGE_TABLE_SIZE, NONE, 0x3);
	}
	for(i = 64; i < ENTRY_COUNT; i++)
		SetEntry(&PageDirPtr_Table[i], NUL, NUL, NONE, NONE);
	
	for(i = 0; i < ENTRY_COUNT * 64; i++){
		if(PageAddress < USER_ADR){
			SetEntry(&PageDir_Table[i], 
					(i * (PAGE_TABLE_SIZE>> 20)) >> 12, PageAddress, NONE, 0x1|0x2|0x80); 
		}
		else{
			SetEntry(&PageDir_Table[i], 
					(i * (PAGE_TABLE_SIZE>> 20)) >> 12, PageAddress, NONE, 0x1|0x2|0x80|0x4); 
		}
			PageAddress = PageAddress + PAGE_SIZE;
	}
}

void SetEntry(PET* PageEntry,
			page_uint_32t Up_Adr,page_uint_32t Low_Adr,
			page_uint_32t Up_Flag,page_uint_32t Low_Flag)
{
	PageEntry->LowerBaseAddress=Low_Adr | Low_Flag;
	PageEntry->UpperBaseAddress=(Up_Adr&0xFF) | Up_Flag;
}
