#ifndef __ducky_mm_h__
#define __ducky_mm_h__

#define PAGE_SHIFT    8
#define PAGE_SIZE     256
#define PAGE_MASK     0xFFFFFF00


#define PTE_READ      0x01
#define PTE_WRITE     0x02
#define PTE_EXECUTE   0x04
#define PTE_DIRTY     0x08

#endif // !__ducky_mm_h__
