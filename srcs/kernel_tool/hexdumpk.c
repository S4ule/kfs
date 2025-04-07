
#include <stddef.h> // size_t

#include "clib/ctype.h" // isprint
#include "kernel_tool/printk.h"

static size_t
_hexdumpk_get_hex_zero_size(unsigned long n, size_t type_size)
{
	size_t size;

	size = 0;
	if (n == 0)
	{
		return type_size * 2 - 1;
	}
	while (n != 0)
	{
		n /= 16;
		size += 1;
	}
	size = type_size * 2 - size;
	return size;
}

static void
_hexdumpk_print_line(const unsigned char *data, size_t line_size)
{
	size_t hex_size;

	// Print the addr
	hex_size = _hexdumpk_get_hex_zero_size((const unsigned long)data, sizeof(unsigned long));
	printk("0x");
	while (hex_size != 0)
	{
		printk("0");
		hex_size--;
	}
	printk("%x: ", data);

	// Print value hex
	for (size_t i = 0; i < line_size; i++)
	{
		hex_size = _hexdumpk_get_hex_zero_size(data[i], sizeof(unsigned char));
		while (hex_size != 0)
		{
			printk("0");
			hex_size--;
		}
		printk("%x ", data[i]);
	}

	// Print value char
	for (size_t i = 0; i < line_size; i++)
	{
		if (isprint(data[i]) == true && data[i] != ' ')
		{
			printk("%c", data[i]);
		}
		else
		{
			printk(".");
		}
	}
	printk("\n");
	return ;
}

void
hexdumpk(const void *data, size_t max_size)
{
	const unsigned char *addr;
	size_t size;

	size = 0;
	addr = (const unsigned char *)data;
	while (size < max_size)
	{
		if (size + 16 < max_size)
		{
			_hexdumpk_print_line(addr, 16);
			addr += 16;
			size += 16;
		}
		else
		{
			_hexdumpk_print_line(addr, max_size - size);
			size = max_size;
		}
	}

	return ;	
}