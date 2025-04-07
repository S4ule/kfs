
#include "gdt.h" // ...
#include "kernel_tool/printk.h" // debug msg

#define GDT_ADDRESS	0x00000800
#define GDT_MAX_ENTRIES	7

struct s_gdt_mount
{ 
	uint16_t limit;	// The upper 16 bits of all selector limits
	uint32_t base;	// The address of gdt
} __attribute__((packed));

/*
	The GDT
*/
uint64_t			gdt[GDT_MAX_ENTRIES];
struct s_gdt_mount *gdt_ptr = (struct s_gdt_mount *)GDT_ADDRESS;

static void
_gdt_encode_entry(uint64_t *entry, uint32_t base, uint32_t limit, uint16_t flag)
{
	/*
		Encode GDT entry as:
			uint16_t	limit_low;
			uint16_t	base_low;
			uint8_t		base_midle;
			uint8_t		access;		// in flags
			uint8_t		attribute;	// in flags
			uint8_t		base_high;
	*/
	// Create the high 32 bit segment
	(*entry)  =  limit       & 0x000F0000;	// set limit bits 19:16
	(*entry) |= (flag <<  8) & 0x00F0FF00;	// set type, p, dpl, s, g, d/b, l and avl fields
	(*entry) |= (base >> 16) & 0x000000FF;	// set base bits 23:16
	(*entry) |=  base        & 0xFF000000;	// set base bits 31:24
 
	// Shift by 32 to allow for low part of segment
	(*entry) <<= 32;
 
	// Create the low 32 bit segment
	(*entry) |= base  << 16;			// set base bits 15:0
	(*entry) |= limit  & 0x0000FFFF;	// set limit bits 15:0
	return ;
}


void
gdt_set_entry(size_t entry, uint32_t base, uint32_t limit, uint16_t flag)
{
	if (entry >= GDT_MAX_ENTRIES)
	{
		printk("GDT entry is out of scope");
		return ;
	}
	else if (limit > 0xFFFFF)
	{
		printk("GDT cannot encode limits larger than 0xFFFFF");
		return ;
	}
	_gdt_encode_entry(&gdt[entry], base, limit, flag);
	return ;
}

/*
	define default segement for GDT init fonction
*/
#define GDT_CODE_PL0	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(0)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL0	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(0)     | SEG_DATA_RDWR

#define GDT_STACK_PL0	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(0)     | SEG_DATA_RDWREXPD
 
#define GDT_CODE_PL3	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(3)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL3	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(3)     | SEG_DATA_RDWR

#define GDT_STACK_PL3	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(3)     | SEG_DATA_RDWREXPD


extern void asm_load_gdt(struct s_gdt_mount *);

void
gdt_initialize(void)
{
	gdt_set_entry(0, 0, 0, 0);	// null
	gdt_set_entry(1, 0, 0x000FFFFF, GDT_CODE_PL0);	// kernel code (kernel binary)
	gdt_set_entry(2, 0, 0x000FFFFF, GDT_DATA_PL0);	// kernel data (kernel heap)
	gdt_set_entry(3, 0, 0x000FFFFF, GDT_STACK_PL0);	// kernel stack
	gdt_set_entry(4, 0, 0x000BFFFF, GDT_CODE_PL3);	// user code (user-executed binaries)
	gdt_set_entry(5, 0, 0x000BFFFF, GDT_DATA_PL3);	// user data (user heap)
	gdt_set_entry(6, 0, 0x000BFFFF, GDT_STACK_PL3);	// user stack

	for (size_t i = 7; i < GDT_MAX_ENTRIES; i++)
	{
		gdt_set_entry(i, 0, 0, 0);	// null
	}

	gdt_ptr->limit = (sizeof(uint64_t) * GDT_MAX_ENTRIES) - 1;
	gdt_ptr->base = (uint32_t)&gdt;
	asm_load_gdt(gdt_ptr);
	return ;
}