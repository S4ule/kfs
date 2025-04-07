
# SRCS
C_SRCS		=	clib/string.c\
				clib/ctype.c\
				clib/stdlib.c\
				kernel_tool/terminal.c\
				kernel_tool/printk.c\
				kernel_tool/hexdumpk.c\
				kernel.c\
				gdt.c

NASM_SRCS	=	boot.asm\
				asm_kernel/interrupts.asm\
				asm_kernel/stack.asm\
				asm_kernel/gdt.asm

# -------------------------------
# Compilation Seting
OS_NAME	=	42os
CC		=	"./compiler/i386_elf_gcc/bin/i386-elf-gcc"
NASM	=	nasm
SRC_DIR	=	./srcs
OBJ_DIR	=	./.objs
INC_DIR	=	-I ./include
ISO_DIR	=	./iso_file
LD_FILE	=	./linker.ld

# -------------------------------
# User controllable preprocessor flags.
CFLAGS		=	-Wall -Wextra -Werror \
				-g2 -O2 \
				-pipe -m32\
				-std=gnu99\
				-ffreestanding\
				-fno-builtin\
				-fno-stack-protector\
				-nostdlib\
				-nodefaultlibs

# --TODO--
#override CFLAGS += \
#    -Wall \
#    -Wextra \
#    -std=gnu11 \
#    -ffreestanding \
#    -fno-stack-protector \
#    -fno-stack-check \
#    -fno-PIC \
#    -m64 \
#    -march=x86-64 \
#    -mno-80387 \
#    -mno-mmx \
#    -mno-sse \
#    -mno-sse2 \
#    -mno-red-zone \
#    -mcmodel=kernel

NASMFLAG	=	-Wall -O2 -f elf32

LDFLAGS		=	-lgcc\
				-nostdlib \
				-static \
				-z max-page-size=0x1000 \
				-T $(LD_FILE)

# -------------------------------
# auto
OBJS	=	$(addprefix $(OBJ_DIR)/,$(C_SRCS:.c=.c.o) $(NASM_SRCS:.asm=.asm.o))

# -------------------------------
# Rules for compilation

default:
	make all

# Link rules for the final executable.
$(OS_NAME).bin: $(LD_FILE) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(INC_DIR) $(OBJS) $(LDFLAGS) -o $(OS_NAME).bin

# Compilation rules for *.c files.
$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

# Compilation rules for *.asm (nasm) files.
$(OBJ_DIR)/%.asm.o: $(SRC_DIR)/%.asm
	$(NASM) $(NASMFLAG) $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	mkdir $(OBJ_DIR)/clib
	mkdir $(OBJ_DIR)/asm_kernel
	mkdir $(OBJ_DIR)/kernel_tool

$(OS_NAME).iso: $(OS_NAME).bin $(ISO_DIR)
	cp $(OS_NAME).bin $(ISO_DIR)/boot/$(OS_NAME).bin
	cp ./grub/grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(OS_NAME).iso $(ISO_DIR)

$(ISO_DIR):
	mkdir $(ISO_DIR)
	mkdir $(ISO_DIR)/boot/
	mkdir -p $(ISO_DIR)/boot/grub

$(OS_NAME):	$(OS_NAME).iso

all:	$(OS_NAME)

# -------------------------------
# Other's rules

test:
	grub-file --is-x86-multiboot $(OS_NAME).bin

run:
	qemu-system-i386 -cdrom $(OS_NAME).iso
	
run_kernel:
	qemu-system-i386 -kernel $(OS_NAME).bin


# -------------------------------
# cleaning
clean:
	rm -f $(OBJS)
	rm -Rf $(ISO_DIR)
	rm -Rf $(OBJ_DIR)

fclean:		clean
	rm -f $(OS_NAME).bin
	rm -f $(OS_NAME).iso

re:
	make fclean
	make all
# -------------------------------

.PHONY:	default all\
		clean fclean re\
		test run run_kernel
