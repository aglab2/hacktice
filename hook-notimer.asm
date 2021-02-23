	
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
addiu sp, sp, 0xffec; don't get rid of those extra things. they are needed
sw a0, 0x4(sp)
sw a1, 0x8(sp)
sw ra, 0xc(sp)

NOP
; executes once here at start up

lw a0, 0x4(sp); don't get rid of those extra things. they are needed
lw a1, 0x8(sp)
or a0, r0, r0
jal 0x80277ee0
lui a1, 0x8000
lui a0, 0x8034
lui a1, 0x8034
addiu a1, a1, 0xb044
addiu a0, a0, 0xb028
jal 0x803225a0
addiu a2, r0, 0x1
lw ra, 0xc(sp)
jr ra
addiu sp, sp, 0x14

execeveryframe:
addiu sp, sp, 0xffe8; don't get rid of those extra things. they are needed
sw ra, 0x14(sp)

lw at, 0x8004e000
jalr at
nop

; -------------------------------------------------------------------------------------- every frame

addiu t6, r0, 0x1; don't get rid of those extra things. they are needed
lui at, 0x8039
lw ra, 0x14(sp)
jr ra
addiu sp, sp, 0x18

execviframes:
addiu sp, sp, 0xffe8
sw ra, 0x18(sp)
sw s5, 0x14(sp)

lw at, 0x8004e004
jalr at
nop

; -------------------------------------------------------------------------------------- every vi frame here

lw ra, 0x18(sp)
addiu sp, sp, 0x18
jr ra
lw ra, 0x14(sp)

nop
nop
nop
nop

code_end: