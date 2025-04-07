; The stack on x86 must be 16-byte aligned according to the System V ABI standard and de-facto extensions.
; The compiler will assume the stack is properly aligned and failure to align the stack will result in undefined behavior.

[bits 32]
global g_stack_bottom
global g_asm_stack_top

section .bss
	align 16
g_stack_bottom:
	resb 16384 ; 16 KiB
	; can use 8192 for 8 KiB
g_asm_stack_top: