
#include "kernel_tool/terminal.h"
#include "clib/string.h"

#include <stddef.h> // size_t
#include <stdint.h>	// uintX_t intX_t

uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

static inline uint8_t
_vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t
_vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

static void
_terminal_putc_at(char c, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = _vga_entry(c, terminal_color);
}

static void
_terminal_scrolling(void)
{
	for (size_t y = 1; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;

			terminal_buffer[index - VGA_WIDTH] = terminal_buffer[index];
		}
	}

	for (size_t x = 0; x < VGA_WIDTH; x++)
	{
		const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;

		terminal_buffer[index] = _vga_entry(' ', terminal_color);
	}
	return ;
}

void
terminal_putchar(char c) 
{
	static size_t terminal_row = 0;
	static size_t terminal_column = 0;

	switch (c)
	{
		case '\r':
		{
			terminal_row = 0;
			break ;
		}
		case '\n':
		{
			terminal_column = 0;

			if (terminal_row + 1 == VGA_HEIGHT)
			{
				_terminal_scrolling();				
			}
			else
			{
				terminal_row += 1;
			}
			break ;
		}
		default:
		{
			_terminal_putc_at(c, terminal_column, terminal_row);
			
			if (++terminal_column == VGA_WIDTH)
			{
				terminal_column = 0;
				if (terminal_row + 1 == VGA_HEIGHT)
				{
					_terminal_scrolling();
				}
				else
				{
					terminal_row += 1;
				}
			}
			break ;
		}
	}	
	return ;
}

inline void
terminal_set_color(enum vga_color fg, enum vga_color bg) 
{
	terminal_color = _vga_entry_color(fg, bg);
}

void terminal_initialize(void) 
{
	terminal_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;

			terminal_buffer[index] = _vga_entry(' ', terminal_color);
		}
	}
}

void terminal_putstr(const char* data) 
{
	size_t size;

	size = strlen(data);
	for (size_t i = 0; i < size; i++)
	{
		terminal_putchar(data[i]);
	}
	return ;
}