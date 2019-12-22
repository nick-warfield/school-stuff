@ Calculator project

@ Sytem commands
.equ	SWI_EXIT, 0x11
.equ	SWI_ALLOCATE, 0x12
.equ	SWI_DEALLOCATE, 0x13	
.equ	SWI_TIME, 0x6d

@ output commands
.equ	SWI_8SEG, 0x200
.equ	SWI_LED, 0x201
.equ	SWI_LCD_STRING, 0x204
.equ	SWI_LCD_INT, 0x205
.equ	SWI_LCD_CLEAR, 0x206
.equ	SWI_LCD_CLEAR_LINE, 0x208

@ input commands
.equ	SWI_BLKBTN, 0x202
.equ	SWI_NUMPAD, 0x203

@ 8 segment references
.equ	SEG_1, 0x80
.equ	SEG_2, 0x40
.equ	SEG_3, 0x20
.equ	SEG_4, 0x08
.equ	SEG_5, 0x04
.equ	SEG_6, 0x02
.equ	SEG_7, 0x01
.equ	SEG_8, 0x10

@ led & black button references
.equ	BLANK, 0x00
.equ	RIGHT, 0x01
.equ	LEFT, 0x02
.equ	BOTH, 0x03

.global	_start

@ r3 = current total
@ r4 = current number input
@ r5 = projected total
@ r6 = blink timer
.text
_start:
	bl	Blink

	@ r1 = blkbtn && r2 = numpad
	bl	GetInput

	@ check for reset
	teq	r1, #RIGHT
	teqne	r1, #LEFT
	beq	Reset

	@ check if numpad was not pressed
	teq	r2, #0
	beq	_start

	@ convert numpad input to indexable value, then lookup its code
	bl	log2
	ldr	r1, =NumpadCode
	ldr	r1, [r1, r2, lsl #2]

	@ >= 0 are nums, < 0 are operation codes
	cmp	r1, #0
	blge	HandleNumber
	bllt	HandleOperation

	bl	PrintCalc
	b	_start

Return:	mov	pc, lr

@ stores inputs into appropriate registers
GetInput:
	@ reset input registers
	mov	r1, #0
	mov	r2, #0

	@ check black buttons
	swi	SWI_BLKBTN
	mov	r1, r0

	@ check numpad
	swi	SWI_NUMPAD
	mov	r2, r0

	b	Return

Blink:
	swi	SWI_TIME
	sub	r0, r0, r6
	cmp	r0, #500
	movge	r0, #0
	swige	SWI_LED

	b	Return

HandleNumber:
@ use this if i want to use double digit numbers
@	mul	r3, r3, #10
@	add	r3, r3, r1

	@ save input
	mov	r3, r1

	@ blink
	mov	r0, #BOTH
	swi	SWI_LED
	swi	SWI_TIME
	mov	r6, r0

	@ display digit
	ldr	r2, =Digits
	ldr	r0, [r2, r1, lsl#2]
	swi	SWI_8SEG

	b	Return

HandleOperation:
	@ check for invalid op code
	cmp	r1, #-2
	blt	PrintError

	mov	r0, #0
	swi	SWI_8SEG
	ldr	r2, =Sign

	@ add case
	cmp	r1, #-1
	addeq	r4, r4, r3
	ldreq	r0, =Plus

	@ subtract case
	cmp	r1, #-2
	subeq	r4, r4, r3
	ldreq	r0, =Minus

	ldr	r0, [r0]
	str	r0, [r2]
	mov	r3, #0
	b	Return

log2:
	mov	r1, #0
loop:	teq	r2, #1
	movne	r2, r2, lsr#1
	addne	r1, r1, #1
	bne	loop

	mov	r2, r1
	b	Return

numOfDigits:
	mov	r0, #1
	ldr	r1, =Divisor

loop2:	cmp	r2, #10
	blt	Return

	add	r0, r0, #1
	sub	r2, r2, r2, lsr #30
	mul	r2, r1, r2
	b	loop2

@ displays register contents in a sensible fashion
PrintCalc:
	@ left aligned text
	mov	r0, #1
	mov	r1, #0
	ldr	r2, =Total
	swi	SWI_LCD_STRING

	mov	r1, #1
	ldr	r2, =Input
	swi	SWI_LCD_STRING
	
	@ register values
	mov	r2, r4
	bl	numOfDigits
	rsb	r0, r0, #38
	mov	r1, #0
	mov	r2, r4
	swi	SWI_LCD_INT

	mov	r2, r3
	bl	numOfDigits
	rsb	r0, r0, #38
	mov	r1, #1
	mov	r2, r3
	swi	SWI_LCD_INT

	@ line 3
	mov	r0, #31
	mov	r1, #2
	ldr	r2, =Sign

	swi	SWI_LCD_STRING
	mov	r0, #32
	ldr	r2, =HLine
	swi	SWI_LCD_STRING

	@ clear error messages
	mov	r0, #6
	swi	SWI_LCD_CLEAR_LINE
	mov	r0, #7
	swi	SWI_LCD_CLEAR_LINE

	b	Return

PrintError:
	mov	r0, #1
	mov	r1, #6
	ldr	r2, =InvalidInput1
	swi	SWI_LCD_STRING

	mov	r1, #7
	ldr	r2, =InvalidInput2
	swi	SWI_LCD_STRING

	b	_start

@ reset calculator contents to initial state
Reset:
	mov	r3, #0
	mov	r4, #0

	@ blink led
	mov	r0, r1
	swi	SWI_LED
	swi	SWI_TIME
	mov	r6, r0

	@ clear 8 segment & lcd display
	mov	r0, #0
	swi	SWI_8SEG
	swi	SWI_LCD_CLEAR

	b	_start


.data
@ holds the string that the screen prints
HLine:	.asciz	"¯
	.align

Total:	.asciz	"Total:"
	.align

Input:	.asciz	"Input:"
	.align

Sign:	.word	0
Plus:	.asciz	"+"
	.align

Minus:	.asciz	"-"
	.align

Mult:	.asciz	"*"
	.align

Divide:	.asciz	"/"
	.align


Divisor:.word	0x1999999a

@ an array for getting the correct 8 segment display
Digits:
	.word	SEG_1|SEG_2|SEG_3|SEG_4|SEG_5|SEG_7		@ 0
	.word	SEG_2|SEG_3					@ 1
	.word	SEG_1|SEG_2|SEG_4|SEG_5|SEG_6			@ 2
	.word	SEG_1|SEG_2|SEG_3|SEG_4|SEG_6			@ 3
	.word	SEG_2|SEG_3|SEG_6|SEG_7				@ 4
	.word	SEG_1|SEG_3|SEG_4|SEG_6|SEG_7			@ 5
	.word	SEG_1|SEG_3|SEG_4|SEG_5|SEG_6|SEG_7		@ 6
	.word	SEG_1|SEG_2|SEG_3				@ 7
	.word	SEG_1|SEG_2|SEG_3|SEG_4|SEG_5|SEG_6|SEG_7	@ 8
	.word	SEG_1|SEG_2|SEG_3|SEG_6|SEG_7			@ 9
	.word	0						@ blank

NumpadCode:
	.word	7
	.word	8
	.word	9
	.word	-2	@ minus code
	.word	4
	.word	5
	.word	6
	.word	-1	@ plus code
	.word	1
	.word	2
	.word	3
	.word	-4	@ divide code
	.word	-6	@ delete code
	.word	0
	.word	-5	@ equals code
	.word	-3	@ multiply code

AsciiDigit:
	.word	0x30	@ 0
	.word	0x31	@ 1
	.word	0x31	@ 2
	.word	0x33	@ 3
	.word	0x34	@ 4
	.word	0x35	@ 5
	.word	0x36	@ 6
	.word	0x37	@ 7
	.word	0x38	@ 8
	.word	0x39	@ 9

@ error message for invalid input, gets displayed on screen
InvalidInput1:
	.asciz	"Invalid input."
	.align
InvalidInput2:
	.asciz	"Press 0-9, +, or - buttons."
	.align
