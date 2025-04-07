[bits 32]
section .text

global asm_interrupts_enable
asm_interrupts_enable:
	sti
	ret

global asm_interrupts_disable
asm_interrupts_disable:
	cli
	ret