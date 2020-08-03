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


		/*kSetPageEntryData( &( pstPDEntry[ i ] ), 
                ( i * ( PAGE_DEFAULTSIZE >> 20 ) ) >> 12, dwMappingAddress, 
                PAGE_FLAGS_DEFAULT | PAGE_FLAGS_PS, 0 );*/ 
                
        //32비트 page_uint_32t 에서 표현 가능한 최대 주소는 4GB 이고, 이 이상은 오버플로우로 다시 0으로 내려가게 됨 
		//따라서 dwMappingAddress 에서 4GB(32bit) / 2MB(21bit) = 2Kb(,2048,11bit) 
		//그리고 페이지 사이즈은 2MB 를 >>20 했을때 남는 값은 항상 2, 그리고 >>12를 했을때 몫이 1 이상일려면 2의 12승은 4096(4KB), i가 4096이어야함
		// 근데  페이지 사이즈은 2MB 를 >>20 했을때 남는 값은 항상 2이므로 i가 2048 일때 i는 4096이 됨 
		// 또한 페이지 디렉터리 테이블의 엔트리는 512개, 테이블의 개수는 64개, 테이블 하나당 2Mb * 512 로 1GB 를 표현 가능 
		//따라서 i가 2048(*2 ->페이지 사이즈은 2MB 를 >>20 했을때 남는 값 2 )일때 i를 페이지 디렉터리 테이블의 엔트리 개수인 512로 나누면 4, 즉 4GB 
		// 이때 32비트는 4GB 까지만 표현 가능하니 dwMappingAddress 에서는 오버플로우로 0이되고, 이에따라 상위 기준 주소에 값을 넣어 4GB 이상을 표현  
		
		//PDT		//    ↓여기까지가 속성 비트,21 비트  
		/*0000 0000 001 | 0 0000 0000 0000 0000 0011      2Mb | Page_Present=1,Page_RW=1 
  		   1    2    3       4    5    6    7    8    */

