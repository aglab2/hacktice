; +++ Prepare common codes
.orga 0x57E9C
	NOP
.orga 0x57EC0
	NOP

; Stars always yellow
;.orga 0xAD548
;	B 0xAD56C
;.orga 0x65FC4
;	B 0x65Fd4

; Timer
; Centiseconds
.orga 0x9EA63
	.db 0xB4

.orga 0x9E9C8
	ADDIU AT, R0, 0xA

.orga 0x9EA00
	MULT T9, AT
	MFLO T1
	ADDIU AT, R0, 3
	DIV T1, AT
	MFLO T2
	SH T2, 0x24(SP)
	
.orga 0x4688
	SB K1, 0xB25E(AT)
.orga 0x4694
	NOP

; timer part
; show the timer
;.orga 0x6194
;	ORI T2, T1, 0x40
; stop the timer condition
;.orga 0x8C7C
;	SB R0, 0xEE(T5)

; dont reset timer between area
.orga 0x5150
	NOP

.orga 0x5024
	B 0x503C
	
; hide timer text
.orga 0x9EA24
	nop
	
; +++Pause menu hooks

; 02011cc8 - 02011d50
.orga 0x978FC
	lw at, 0x8004e004
	jalr at
	nop
	b 0x97A38
	nop

.orga 0x96838
	lui t2, 0x0201
	addiu t2, t2, 0x1cc8
.orga 0x968fc
	lui t0, 0x0201
	addiu t0, t0, 0x1d50

.orga 0x9688C
	lw at, 0x8004e004
	jalr at
	nop
	b 0x968D4
	nop

.orga 0x96984
	b 0x96AD8
	nop

; +++ Music hook

.orga 0xd8068
	addiu sp, sp, -0x18
	sw ra, 0x14(sp)
	lw at, 0x8004e008
	jalr at
	nop
	lw ra, 0x14(sp)
	jr ra
	addiu sp, sp, 0x18

; +++ check_death_barrier hack
.orga 0xb5fc
.area 0x4C, 0x00
	lw at, 0x8004e00c
	jalr at
	lw a0, 0x18(sp)
	b 0xb64c
	nop
.endarea

; +++ Main hook to load data in

.headersize 0x80245000

; notes about the spaces to put code in
; there is space in rom from 0x7cc6c0 to 0x800000
; there is space in ram from 0x80367500 to 0x80378700 (can fit in 17536 lines)

.definelabel code_rom, 0x7f1200; where your code goes in the rom
.definelabel code_ram, 0x8005c000-0xEE00; where your code goes in the ram
.definelabel code_end_copy, 0xEE00+code_rom

.orga 0x396c; here it copies code into the ram at start up
	li a0, code_ram
	li a1, code_rom
	li.u a2, code_end_copy
	jal 0x80278504
	li.l a2, code_end_copy
	jal execonce
	nop

.orga 0xfd354
	jal execeveryframe
	nop

; FIXME: crashes on VC
;.orga 0xde270; responsible for running every VI frames
;b 0x803232a4
;sw t4, 0x7110(at)
;.skip 28
;lw ra, 0x1c(sp)
;lw s0, 0x18(sp)
;jr ra
;addiu sp, sp, 0x38
;lb s7, code_ram
;nop
;beqz s7, @@skip_vi_frames
;nop
;add s5, r0, ra
;jal execviframes
;nop
;@@skip_vi_frames:
;b 0x80323278
;lui at, 0x8036

.headersize (code_ram - code_rom)

.orga code_rom
execonce:
	addiu sp, sp, -0x18
	sw ra, 0x14(sp)
	or a0, r0, r0
	jal 0x80277ee0
	lui a1, 0x8000
	lui a0, 0x8034
	lui a1, 0x8034
	addiu a1, a1, 0xb044
	addiu a0, a0, 0xb028
	jal 0x803225a0
	addiu a2, r0, 0x1
	lw ra, 0x14(sp)
	jr ra
	addiu sp, sp, 0x18
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

.orga code_rom+0x100
execeveryframe:
	addiu sp, sp, 0xffe8
	sw ra, 0x14(sp)

	lw at, 0x8004e000
	jalr at
	nop

	addiu t6, r0, 0x1; don't get rid of those extra things. they are needed
	lui at, 0x8039
	lw ra, 0x14(sp)
	jr ra
	addiu sp, sp, 0x18

	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

.orga code_rom+0x200
disable:
	addiu sp, sp, 0xffe8
	sw ra, 0x14(sp)

	lw t1, 0x8004E018
	li t0, 1146307148
	beq t0, t1, nowriteback
	NOP

	; osWritebackDCache(0x8004e000, 0xE000)
	li a0, 0x8004e000
	jal 0x80325d20
	li a1, 0xE000

	li t0, 1146307148
	sw t0, 0x8004E018

nowriteback:
	lw ra, 0x14(sp)
	jr ra
	addiu sp, sp, 0x18
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

.orga code_rom+0x300
upgrade:
	addiu sp, sp, 0xffe8
	sw ra, 0x14(sp)

	lw t1, 0x8004E018
	li t0, 1431324498
	beq t0, t1, noinval
	NOP

	; osInvalICache(0x8004e000, 0xE000)
	li a0, 0x8004e000
	jal 0x80324610
	li a1, 0xE000

	; osInvalDCache(0x8004e000, 0xE000)
	li a0, 0x8004e000
	jal 0x803243b0
	li a1, 0xE000
	
	li t0, 1431324498
	sw t0, 0x8004E018

noinval:
	lw ra, 0x14(sp)
	jr ra
	addiu sp, sp, 0x18
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

;execviframes:
	;addiu sp, sp, 0xffe8
	;sw ra, 0x18(sp)
	;sw s5, 0x14(sp)

	;lw at, 0x8004e004
	;jalr at
	;nop

	; -------------------------------------------------------------------------------------- every vi frame here

	;lw ra, 0x18(sp)
	;addiu sp, sp, 0x18
	;jr ra
	;lw ra, 0x14(sp)

	;nop
	;nop
	;nop
	;nop
