#include <stdbool.h>	// true/false
#include <stddef.h>		// size_t
#include <stdint.h>		// uintX_t intX_t

#include "gdt.h"
#include "kernel_tool/terminal.h"
#include "kernel_tool/printk.h"
#include "kernel_tool/hexdumpk.h"
#include "asm_kernel/interrupts.h"
#include "asm_kernel/stack.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This program will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
# error "This needs to be compiled with a ix86-elf compiler"
#endif

void put_42(void)
{
	terminal_set_color(VGA_COLOR_CYAN, VGA_COLOR_BLACK);
	printk("                                                                  \n");
	printk("         :::     ::::::::          :::    ::: :::::::::: :::::::: \n");
	printk("       :+:     :+:    :+:         :+:   :+:  :+:       :+:    :+: \n");
	printk("     +:+ +:+        +:+          +:+  +:+   +:+       +:+         \n");
	printk("   +#+  +:+      +#+            +#++:++    :#::+::#  +#++:++#++   \n");
	printk(" +#+#+#+#+#+  +#+              +#+  +#+   +#+              +#+    \n");
	printk("      #+#   #+#               #+#   #+#  #+#       #+#    #+#     \n");
	printk("     ###  ##########         ###    ### ###        ########       \n");
	printk("                                                                  \n");
	terminal_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	printk("\n");
	return ;
}

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	
	/* 42 :) */
	put_42();

	/* GDT */
	asm_interrupts_disable();
	gdt_initialize();

	/* keyboard work with interrupts */
	// asm_interrupts_enable();

	return ;
}
