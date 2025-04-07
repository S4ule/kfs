; doc:
; http://wiki.osdev.org/Bare_Bones

[bits 32]
section .multiboot
	align 4
	dd 0x1BADB002	; Magic number
	dd 0x0			; architecture 0 (protected mode i386)
	dd - (0x1BADB002 + 0x0)	; Checksum


section .text

extern g_asm_stack_top
extern kernel_main

global _start
_start:
	; The bootloader has loaded us into 32-bit protected mode on a x86 machine.
	; Interrupts are disabled.
	; Paging is disabled.
	; The processor state is as defined in the multiboot standard.

	; Setup the stack (it grows downwards on x86 systems)
	mov esp, g_asm_stack_top

	; Enter the high-level kernel.
	; /!\ The ABI requires the stack is 16-byte aligned at the time of the call instruction.
	call kernel_main

	; It doesn't make sense to return from this function as the bootloader is gone.
	; If the system has nothing more to do, put the computer into an infinite loop.
	jmp .infinit_loop

.infinit_loop:
	cli
	hlt
	jmp .infinit_loop




