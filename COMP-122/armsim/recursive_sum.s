@ create a program that prints the sum an integer and all positive numbers less than it

@ system commands
.equ	SWI_EXIT, 0x11
.equ	SWI_TIME, 0x6d
.equ	SWI_OPEN, 0x66
.equ	SWI_CLOSE, 0x68
.equ	SWI_READ, 0x6c
.equ	SWI_PRINT_INT, 0x6b
.equ	SWI_PRINT_STRING, 0x69

@ file modes
.equ	StdOut, 1
.equ	StdIn, 0

.global _start


.text
_start:
	swi	SWI_TIME
	mov	r4, r0

	ldr	r0, =InFile
	mov	r1, #StdIn
	swi	SWI_OPEN
	bcs	FileError_DNE

	ldr	r1, =InFileHandle
	str	r0, [r1]

	swi	SWI_READ
	bcs	FileError_Empty
	mov	r5, r0

sumLoop:
/*
	@ recursively sum input
	add	r3, r3, r0
	sub	r0, r0, #1
	teq	r0, #0
	bne	sumLoop
*/
	@ sum formula
	mov	r3, r0, lsr #1
	add	r0, r0, #1
	mul	r3, r3, r0

	@ calculate delta
	swi	SWI_TIME
	sub	r2, r0, r4
	mov	r4, r0

	@ print input
	mov	r0, #StdOut
	ldr	r1, =Message3
	swi	SWI_PRINT_STRING
	mov	r1, r5
	swi	SWI_PRINT_INT
/*
	@ print sum
	ldr	r1, =Message1
	swi	SWI_PRINT_STRING
	mov	r1, r3
	swi	SWI_PRINT_INT
*/	
	@ print delta time
	ldr	r1, =Message2
	swi	SWI_PRINT_STRING
	mov	r1, r2
	swi	SWI_PRINT_INT
	ldr	r1, =Gap
	swi	SWI_PRINT_STRING

	@ read next input
	ldr	r0, =InFileHandle
	ldr	r0, [r0]
	swi	SWI_READ
	
	@ if there is anther input, reset and loop again
	movcc	r3, #0
	movcc	r5, r0
	bcc	sumLoop

	@ close file and exit
	ldr	r0, =InFileHandle
	swi	SWI_CLOSE

Exit:	swi	SWI_EXIT

FileError_DNE:
	mov	r0, #StdOut
	ldr	r1, =FE_DNE
	swi	SWI_PRINT_STRING
	b	Exit

FileError_Empty:
	ldr	r0, =InFile
	swi	SWI_CLOSE
	mov	r0, #StdOut
	ldr	r1, =FE_Empty
	swi	SWI_PRINT_STRING
	b	Exit


.data
InFile:		.asciz	"integers.dat"
		.align
InFileHandle:	.word	0
FE_DNE:		.asciz	"ERROR: 'integers.dat' file does not exsist."
		.align
FE_Empty:	.asciz	"ERROR: 'integers.dat' file contains no valid data."
		.align
Message1:	.asciz	"\nRecursive Sum: "
		.align
Message2:	.asciz	"\tDelta Time: "
		.align
Message3:	.asciz	"Input: "
		.align
Gap:		.asciz	"\n"
		.align

