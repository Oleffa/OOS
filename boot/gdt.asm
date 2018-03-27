; Set up a Global Descriptor Table

; The GDT is a structure that contains information about memory segments
; for example: base address, size, access privileges
; GDT: global
; LDT: local, contain memory segemnts private to specific programs
; In order to reference a segment a program must use its index inside the GDT or LDT

; An GDT entry consists of 8 bytes
; Byte		Name		Bits
;===================================
; 0		Limit		0-7
; 1		Limit		8-15
; 2		Base		0-7
; 3		Base		8-15
; 4		Base		16-23
; 5		Accessbyte	0-7
; 6		Limit		16-19
; 7		Flags		0-3
; 8		Base		24-31

; Limit: Size of segment (in bytes or 4kb units depending on flags)
; Base: Start address of the segment
; Accessbyte: Access information (Ring, executable, etc)
; Flags: Segment size (16/32 Bit)

gdt_start:

; 1st Element: null descriptor (mandatory)
gdt_null:	
	dd 0x0		; define a double word (4 bytes)
	dd 0x0

; 2nd Element, base address is 0, limit is 4GB, 4kbyte segment size, 32 bit opcodes
gdt_code:
	dw 0xffff	; Limit (bits 0-15)
	dw 0x0 		; Base (bits 0-15)
	db 0x0 		; Base (bits 16-23)
	db 10011010b	; 1st Flags, type flags
	db 11001111b	; 2nd Flags, Limit (bits 16-19)
	db 0x0 		; Base (bits 24 - 31)

; 3rd entry: Data segment descriptor, same as code segment but the descriptor type
; says its a data segment
gdt_data:
	dw 0xffff	; Limit (bits 0-15)
	dw 0x0 		; Base (bits 0-15)
	db 0x0 		; Base (bits 16-23)
	db 10010010b	; 1st Flags, type flags
	db 11001111b	; 2nd Flags, Limit (bits 16-19)
	db 0x0 		; Base (bits 24 - 31)

; Label used for calculating the size of the GDT in assembler
gdt_end:

; GDT descriptor
gdt_descriptor:
	dw gdt_end - gdt_start - 1	; Size of the GDT (-1)
	dd gdt_start 			; Start address of the GDT

; Global variables for GDT segment descriptor offsets
; Define what registers must contain in protected mode
; When DS = 0x10 in PM the CPU knows to use the segment at offset 0x10 in the GDT
; which is the DATA segment
CODE_SEGMENT equ gdt_code - gdt_start
DATA_SEGMENT equ gdt_data - gdt_start


	
