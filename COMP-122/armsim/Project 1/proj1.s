.equ SWI_EXIT, 0X11
.equ SWI_PrintString, 0x69	@ write a null-ending string
.equ SWI_PrintInt, 0x6b	@ write an integer
.equ SWI_Open, 0x66	@ open a file
.equ SWI_Close, 0x68	@ close a file
.equ SWI_Read, 0x6c	@ read an int from opened file
.equ Stdout, 1		@ set output mode
.equ Stdin, 0

@ Generation Bounds
.equ LOST_UPPER, 127
.equ LOST_LOWER, 102
.equ GREAT_UPPER, 101
.equ GREAT_LOWER, 93
.equ BABY_UPPER, 71
.equ BABY_LOWER, 53
.equ X_UPPER, 52
.equ X_LOWER, 38
.equ Y_UPPER, 36
.equ Y_LOWER, 22
.equ Z_UPPER, 21
.equ Z_LOWER, 7

.global _start

.text
_start:
	ldr	r0, =InFileName		@ set name of file to look for
	mov	r1, #Stdin		@ set mode to input
	swi	SWI_Open		@ open file for reading
	bcs	printErrorDNE		@ throw an error if file not found

	ldr	r1, =InFileHandle
	str	r0, [r1]		@ save file location into file handle memory location

	ldr	r0, =InFileHandle	@ loads input file handle
	ldr	r0, [r0]		@ loads input file
	swi	SWI_Read		@ reads an int into r0
	bcs	printErrorEmpty

lostGen:
	cmp	r0, #LOST_LOWER
	blt	greatGen
	cmp	r0, #LOST_UPPER
	bgt	noGen
	add	r4, r4, #1
	b	endCheck

greatGen:
	cmp	r0, #GREAT_LOWER
	blt	babyBoomer
	cmp	r0, #GREAT_UPPER
	bgt	noGen
	add	r5, r5, #1
	b	endCheck

babyBoomer:
	cmp	r0, #BABY_LOWER
	blt	genX
	cmp	r0, #BABY_UPPER
	bgt	noGen
	add	r6, r6, #1
	b	endCheck

genX:
	cmp	r0, #X_LOWER
	blt	genY
	cmp	r0, #X_UPPER
	bgt	noGen
	add	r7, r7, #1
	b	endCheck
 
genY:
	cmp	r0, #Y_LOWER
	blt	genZ
	cmp	r0, #Y_UPPER
	bgt	noGen
	add	r8, r8, #1
	b	endCheck

genZ:
	cmp	r0, #Z_LOWER
	blt	noGen
	cmp	r0, #Z_UPPER
	bgt	noGen
	add	r9, r9, #1
	b	endCheck

noGen:
	add	r10, r10, #1

endCheck:
	ldr	r0, =InFileHandle
	ldr	r0, [r0]
	swi	SWI_Read
	bcc	lostGen

print:
	swi	SWI_Close
	mov	r0, #Stdout

	ldr	r1, =printL
	swi	SWI_PrintString
	mov	r1, r4
	swi	SWI_PrintInt

	ldr	r1, =printG
	swi	SWI_PrintString
	mov	r1, r5
	swi	SWI_PrintInt

	ldr	r1, =printB
	swi	SWI_PrintString
	mov	r1, r6
	swi	SWI_PrintInt

	ldr	r1, =printX
	swi	SWI_PrintString
	mov	r1, r7
	swi	SWI_PrintInt

	ldr	r1, =printY
	swi	SWI_PrintString
	mov	r1, r8
	swi	SWI_PrintInt

	ldr	r1, =printZ
	swi	SWI_PrintString
	mov	r1, r9
	swi	SWI_PrintInt

	ldr	r1, =printNA
	swi	SWI_PrintString
	mov	r1, r10
	swi	SWI_PrintInt


EXIT: swi SWI_EXIT


printErrorDNE:
	mov	r0, #Stdout
	ldr	r1, =InFileDNE
	swi	SWI_PrintString
	b	EXIT

printErrorEmpty:
	swi	SWI_Close
	mov	r0, #Stdout
	ldr	r1, =InFileEmpty
	swi	SWI_PrintString
	b	EXIT


.data
InFileName:	.asciz "integers.dat"
		.align
InFileHandle:	.word	0
InFileDNE:	.asciz "Unable to locate integers.dat file\n"
		.align
InFileEmpty:	.asciz "integers.dat contains no data\n"
		.align

printG:	.asciz "\nGreatest Generation:     "
	.align
printL:	.asciz "Lost Generation:         "
	.align
printB:	.asciz "\nBaby Boomer Generation:  "
	.align
printX:	.asciz "\nGeneration X:            "
	.align
printY:	.asciz "\nGeneration Y:            "
	.align
printZ:	.asciz "\nGeneration Z:            "
	.align
printNA:.asciz "\nNot Applicable:          "
	.align
