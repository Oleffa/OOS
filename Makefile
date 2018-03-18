# SRCS are all source files that end in .c or .s
SRCS = $(shell find -name '*.[cs]')
# OBJS are all object files
OBJS = $(addsuffix .o,$(basename $(SRCS)))

# Set gcc cross compiler
CC = /home/oli/Workspace/crosscompiler/bin/i686-elf-gcc
# Set linker
LD = ld

# Set flags
CFLAGS = -std=gnu99 -ffreestanding -g -c -I include
LDFLAGS = -ffreestanding -nostdlib -g -T linker.ld


all: start kernel console gdt link clean

start:
	$(CC) $(CFLAGS) start.s -o start.o

kernel:
	$(CC) $(CFLAGS) kernel.c -o kernel.o

console:
	$(CC) $(CFLAGS) console.c -o console.o

gdt:
	$(CC) $(CFLAGS) gdt.c -o gdt.o

link:
	$(CC) $(LDFLAGS) start.o kernel.o console.o gdt.o -o mykernel.elf -lgcc

clean:
	@echo $("hi")
	rm $(OBJS)
