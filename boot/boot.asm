; When the computer is turned on the Processor is jumping in Real Mode and jumps to
; 0xFFFF0 where the BIOS is located. The BIOS is initializing the hardware and then
; calls interrupt 0x19 whos handler loads the bootsector from the harddrive or disk
; to 0x7c00 and jumps there

[org 0x7c00]

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000			; Set the stack, BP = base pointer pointing to the
				; base address of the stack
mov sp, bp			; Move the Stack pointer to the base pointer

call load_kernel

call switch_to_protected

jmp $

; Includes for external functions
%include "switch_to_protected.asm"
%include "gdt.asm"

; Code executed in 16 bit real mode
[bits 16]
; 16 bit registers according to x86 Registers:
; H and L stand for high and low byte
; AX: Accumulator register, I/O port access, arithmetic, interrupt calls
; BX: Base register, base pointer for memory access
; CX: Counter register, loop counter and shifts
; DX: Data Register
load_kernel:
	mov bx, KERNEL_OFFSET
	mov dh, 15
	mov dl, [BOOT_DRIVE]
	call disk_load

	ret

; Load DH sectors to ES (), BX (Base Register, used as base pointer for memory access)
; from Drive DL
disk_load:
	push dx			; Store DX on stack so we can later restore how many
				; sectors were requested to for reading
	mov ah, 0x02		; BIOS read sector function
	mov al, dh		; Read the dh sectors into al
	mov ch, 0x00 		; Set counter register to 0
	mov dh, 0x00		; Select head 0
	mov cl, 0x02 		; Start reading from second sector (after boot sector)
	int 0x13		; BIOS interrupt
	jc disk_error		; Jump if error
	pop dx 			; Restore DX from stack
	cmp dh, al 		; If AL (# of read sectors) != DH (# of Sectors expected)
	jne disk_error 		; Handle error
	ret

disk_error:
	jmp $

call switch_to_protected 	; Move to 32 bit protected mode, never returns back

jmp $

[bits 32]
; 32 Bit protected mode takes over
BEGIN_PM:
	call KERNEL_OFFSET
	jmp $			; Hang


; Global variables
BOOT_DRIVE db 0

; Bootsector padding
times 510-($-$$) db 0		; Fill 512 bytes with zeros
dw 0xaa55			; Needed by some older BIOSes in order to identify a
				; boot sector
