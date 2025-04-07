; void asm_load_gdt(struct s_gdt_mount *);

[bits 32]
section .text
global asm_load_gdt

asm_load_gdt:
	mov eax, [esp + 4]
	lgdt [eax] ; load gdt
	JMP   0x08:.reload_cs
	ret

.reload_cs:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret