#ifndef _PAGING_H_
#define _PAGING_H_

#define ENTRY_COUNT		512
#define PAGE_TABLE_SIZE 0x1000
#define PAGE_SIZE		0x200000 
#define TABLE_ADR		0x106000 

#define NUL				0x00
#define NONE			0x00

#define USER_ADR		0x2000000

typedef unsigned char page_uchar_8t;
typedef unsigned short page_ushort_16t;
typedef unsigned int page_uint_32t;
typedef unsigned long long  page_ulld_64t;

typedef struct PageEntryStruct
{
  /*uchar Page_Present : 1;
	uchar Page_RW : 1;
	uchar Page_US : 1;
	uchar Page_PWT : 1;
	uchar Page_PCD : 1;
	uchar Page_Accessed : 1;
	uchar Page_Ignored_Dont_Modify_1 : 1;
	uchar Page_Reserved_1 : 1; //¹«Á¶°Ç 0 
	uchar Page_Ignored_Dont_Modify_2 : 4;
	page_uint_32t Page_LowerBaseAddress : 20;
	page_uint_32t Page_UpperBaseAddress : 8;
	page_uint_32t Page_Reserved_2: 12;
	page_uint_32t Page_Ignored_Dont_Modify_3 : 11;
	uchar Page_EXD : 1;*/
	page_uint_32t LowerBaseAddress;
	page_uint_32t UpperBaseAddress;
}PML4T, PDPT, PDT, PET;

void MakePageTable(void);
void SetEntry(PET* PageEntry,
			page_uint_32t Up_Adr,page_uint_32t Low_Adr,
			page_uint_32t Up_Flag,page_uint_32t Low_Flag);

#endif 
