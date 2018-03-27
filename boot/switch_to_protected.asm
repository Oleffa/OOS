; Switches from 16 bit real mode to 32 bit protected mode

; x86 Controll registers CR0-CR4
; x86 Debug registers    DR0-DR7
; x86 Test registers	 TR3-TR7
; Protected mode segmentation registers:
; - GDTR (Global Descriptor Table Regsiters)
; - IDTR (Interrupt Descriptor Table Register)
; - LDTR (Local Descriptor Table Register)
; - TR

[bits 16]
switch_to_protected:
	cli			; Turn off interrupts until the switch is done or
				; interrupts can interfer this process

	lgdt[gdt_descriptor]	; Load the global descriptor table which defines the
				; protected mode segments

	mov eax, cr0		; To switch we set the first bit of CR0
	or eax, 0x1

	mov cr0, eax

	jmp CODE_SEGMENT:init_pm	; Big jump to our 32 bit code segment (CPU is
					; flushin cache of pre-fetched and real-mode
					; decoded instructions

[bits 32]
; Init registers and stack when entering 32 bit mode

init_pm:
	mov ax, DATA_SEGMENT 	; Old datasegments are not needed anymore and the
				; pointer is changed to point the segment registers to
				; the data selector defined in the GDT
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ebp, 0x90000	; Update Stack position to be on the top of the free
				; space
	mov esp, ebp 
	call BEGIN_PM		; Jump back 

