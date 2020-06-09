@ Calculator project

@ Sytem commands
.equ	SWI_EXIT, 0x11
.equ	SWI_TIME, 0x6d

@ output commands
.equ	SWI_8SEG, 0x200
.equ	SWI_LED, 0x201
.equ	SWI_LCD_STRING, 0x204
.equ	SWI_LCD_INT, 0x205
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

@ text alignments
.equ	SIGN_ALIGN, 21
.equ	NUM_ALIGN, 38
.equ	PAD_ALIGN, 32

.global	_start
.text
_start:
	@ print left aligned text
	mov	r0, #1
	mov	r1, #0
	ldr	r2, =Setup1
	swi	SWI_LCD_STRING
	mov	r1, #1
	ldr	r2, =Setup2
	swi	SWI_LCD_STRING

	@ print line
	mov	r0, #20
	mov	r1, #2
	ldr	r2, =HLine
	swi	SWI_LCD_STRING

	@ print signs
	mov	r0, #SIGN_ALIGN
	mov	r1, #1
	ldr	r2, =Signs
	add	r2, r2, #4
	swi	SWI_LCD_STRING
	mov	r1, #3
	add	r2, r2, #16
	swi	SWI_LCD_STRING

	@ print default total
	mov	r0, #NUM_ALIGN
	sub	r0, r0, #1
	mov	r1, #0
	mov	r2, #0
	swi	SWI_LCD_INT

	@ print intstructions
	bl	PrintNumpad
	mov	r0, #1
	mov	r1, #10
	ldr	r2, =Instruction1
	swi	SWI_LCD_STRING
	mov	r1, #12
	ldr	r2, =Instruction2
	swi	SWI_LCD_STRING
	mov	r1, #13
	ldr	r2, =Instruction3
	swi	SWI_LCD_STRING
	mov	r1, #14
	ldr	r2, =Instruction4
	swi	SWI_LCD_STRING

update:
	bl	Blink
	bl	GetInput

	@ check black buttons
	ldmfd	sp!, {r0}
	teq	r0, #RIGHT
	beq	Evaluate
	teq	r0, #LEFT
	beq	Delete

	@ check if numpad was not pressed
	ldmfd	sp!, {r0}
	teq	r0, #0
	beq	update

	@ convert numpad input to indexable value, then lookup its code
	mov	r1, #0
	bl	log2
	ldr	r1, =NumpadCode
	ldr	r1, [r1, r0, lsl#2]
	bl	ClearError

	@ > 10 are nums, < 10 are operation codes
	cmp	r1, #10
	blt	HandleNumber
	bge	HandleOperation

@ r1=number pressed
HandleNumber:
	@ update input
	ldr	r4, =Input
	ldr	r0, [r4]
	mov	r3, #10
	mla	r2, r0, r3, r1
	str	r2, [r4]

	@ blink
	mov	r0, #BOTH
	swi	SWI_LED
	stmfd	sp!, {r1}
	bl	SetTimer
	ldmfd	sp!, {r1}

	@ display digit
	ldr	r2, =Digits
	ldr	r0, [r2, r1, lsl#2]
	swi	SWI_8SEG
	mov	r0, r4
	mov	r1, #1
	bl	PrintNum

	b	Compute

HandleOperation:
	@ check if invalid input
	teq	r1, #15
	ldreq	r2, =UseNumpad
	beq	PrintError

	@ update operator
	ldr	r0, =Operation
	sub	r1, r1, #10
	str	r1, [r0]
	bl	PrintOperator

	b	Compute

Compute:
	@ load contents
	ldr	r0, =Operation
	ldr	r0, [r0]
	ldr	r4, =Input
	ldr	r1, [r4]
	ldr	r3, =Total
	ldr	r2, [r3]
	mov	r6, #0

	@ add case
	teq	r0, #1
	addeq	r5, r2, r1
	beq	END

	@ subtract case
	teq	r0, #2
	subeq	r5, r2, r1
	beq	END

	@ multiply case
	teq	r0, #3
	muleq	r5, r2, r1
	beq	END

	@ divide case
	@ throw error when dividing by zero
	teq	r1, #0
	ldreq	r2, =DivByZero
	beq	PrintError

	@ convert negative dividends to positive values
	mov	r5, #0
	cmp	r2, #0
	mvnlt	r2, r2
	addlt	r2, r2, #1
	movlt	r0, #0

	mov	r7, #10

	@ integer division
DIV:	cmp	r2, r1
	subge	r2, r2, r1
	addge	r5, r5, #1
	bge	DIV

	@ get remainder
	teq	r2, #0
	beq	DIVEND
	teq	r6, #3
	beq	DIVEND
	add	r6, r6, #1

	stmfd	sp!, {r5}
	mov	r5, #0
	mov	r8, r2
	mul	r2, r7, r8
	b	DIV

DIVEND:	mov	r8, #0
	stmfd	sp!, {r5}

	@ determine offset
l1:	teq	r6, #0
	beq	l3
	sub	r6, r6, #1
	add	r8, r8, #1

	@ print remainder
l2:	ldmfd	sp!, {r7}
	stmfd	sp!, {r0-r2}
	rsb	r0, r8, #NUM_ALIGN
	mov	r1, #3
	mov	r2, r7
	swi	SWI_LCD_INT
	ldmfd	sp!, {r0-r2}
	b	l1

	@ print period and int component
l3:	ldmfd	sp!, {r7}
	stmfd	sp!, {r0-r2}
	teq	r8, #0
	addne	r8, r8, #1
	rsbne	r0, r8, #NUM_ALIGN
	mov	r1, #3
	ldrne	r2, =Signs
	swine	SWI_LCD_STRING
	addne	r8, r8, #1

	mov	r0, #0
	ldr	r1, =0x1999999a
	mov	r2, r7
	stmfd	sp!, {r2, r3}
	bl	numOfDigits
	ldmfd	sp!, {r2, r3}
	add	r8, r0, r8
	rsb	r0, r8, #NUM_ALIGN
	mov	r1, #3
	swi	SWI_LCD_INT

	ldmfd	sp!, {r0-r2}
	teq	r0, #0
	addeq	r8, r8, #1
	rsbeq	r0, r8, #NUM_ALIGN
	moveq	r1, #3
	ldreq	r2, =Signs
	addeq	r2, r2, #8
	swieq	SWI_LCD_STRING

	moveq	r0, #0
	mov	r5, r7

	@ convert back to negative if needed
	teq	r0, #0
	mvneq	r5, r5
	addeq	r5, r5, #1

END:	ldr	r6, =Operation
	ldr	r6, [r6]
	ldr	r0, =Projected
	str	r5, [r0]

	@ update screen
	stmfd	sp!, {r0, r3, r4}
	teq	r6, #4
	bleq	ClearTop
	blne	ClearAll
	ldmfd	sp!, {r0, r4, r5}

	teq	r6, #4
	movne	r1, #3
	blne	PrintNum

	mov	r0, r4
	mov	r1, #0
	bl	PrintNum
	mov	r0, r5
	mov	r1, #1
	bl	PrintNum

	b	update

Evaluate:
	@ blink
	swi	SWI_LED
	bl	SetTimer
	bl	ClearError

	@ set projected value to be new total
	ldr	r0, =Total
	ldr	r1, =Projected
	ldr	r1, [r1]
	str	r1, [r0]

	@ clear input
	mov	r0, #0
	ldr	r1, =Input
	str	r0, [r1]

	bl	ClearAll

	ldr	r0, =Total
	mov	r1, #0
	bl	PrintNum
	ldr	r0, =Input
	mov	r1, #1
	bl	PrintNum
	ldr	r0, =Projected
	mov	r1, #3
	bl	PrintNum

	b	update

Delete:
	mov	r0, #0
	ldr	r1, =Input
	str	r0, [r1]

	@ clear 8 segment display
	swi	SWI_8SEG
	bl	ClearError

	@ reset on double click
	ldr	r1, =Timestamp
	ldr	r1, [r1]
	swi	SWI_TIME
	cmp	r0, r1
	blt	Reset

	@ blink
	mov	r0, #LEFT
	swi	SWI_LED
	bl	SetTimer

	@ clear input
	bl	ClearInput
	b	update

Reset:
	@ clear contents, and print default state
	mov	r0, #0
	ldr	r1, =Total
	str	r0, [r1]
	bl	ClearAll

	mov	r0, #NUM_ALIGN
	sub	r0, r0, #1
	mov	r1, #0
	mov	r2, #0
	swi	SWI_LCD_INT

	b	update

@ r1=line, r0=numlocation
PrintNum:
	@ load number, and convert to positive
	mov	r3, r0
	ldr	r2, [r3]
	cmp	r2, #0
	mvnlt	r2, r2
	addlt	r2, r2, #1

	@ count digits, then right align
	stmfd	sp!, {r1-r3, lr}
	mov	r0, #1
	ldr	r1, =0x1999999a
	bl	numOfDigits
	ldmfd	sp!, {r1-r3, lr}
	rsb	r0, r0, #NUM_ALIGN
	swi	SWI_LCD_INT

	@ print negative sign if needed
	ldr	r2, [r3]
	cmp	r2, #0
	sublt	r0, r0, #1
	ldrlt	r2, =Signs
	addlt	r2, r2, #8
	swilt	SWI_LCD_STRING
	mov	pc, lr

PrintOperator:
	@ load and print the current operator
	mov	r0, #SIGN_ALIGN
	ldr	r1, =Operation
	ldr	r1, [r1]
	ldr	r2, =Signs
	add	r2, r2, r1, lsl#2
	mov	r1, #1
	swi	SWI_LCD_STRING
	mov	pc, lr

PrintEquals:
	mov	r0, #SIGN_ALIGN
	mov	r1, #3
	ldr	r2, =Signs
	add	r2, r2, #20
	swi	SWI_LCD_STRING
	mov	pc, lr

@ r2 = error message location
PrintError:
	@ print error messages on lines 5 and 6
	mov	r0, #1
	mov	r1, #7
	swi	SWI_LCD_STRING

	mov	r1, #6
	ldr	r2, =InvalidInput
	swi	SWI_LCD_STRING

	b	update

GetInput:
	@ check numpad
	swi	SWI_NUMPAD
	stmfd	sp!, {r0}

	@ check black buttons
	swi	SWI_BLKBTN
	stmfd	sp!, {r0}

	mov	pc, lr

SetTimer:
	@ for led, lasts 250ms
	swi	SWI_TIME
	add	r0, r0, #250
	ldr	r1, =Timestamp
	str	r0, [r1]
	mov	pc, lr

Blink:
	@ check timer, turn off led on time up
	swi	SWI_TIME
	ldr	r1, =Timestamp
	ldr	r1, [r1]
	cmp	r0, r1
	movge	r0, #0
	swige	SWI_LED
	mov	pc, lr

@ expects r0=power of 2, r1=0
@ r0 is an output
log2:
	teq	r0, #1
	movne	r0, r0, lsr#1
	addne	r1, r1, #1
	bne	log2
	mov	r0, r1
	mov	pc, lr

@ expects r0=1, r1=0x1999999a, r2=num
@ r0 is an output
numOfDigits:
	@ divide by 10 until only 1 digit is left
	cmp	r2, #10
	movlt	pc, lr
	add	r0, r0, #1
	sub	r2, r2, r2, lsr#30
	umull	r3, r2, r1, r2
	b	numOfDigits

ClearError:
	mov	r0, #6
	swi	SWI_LCD_CLEAR_LINE
	mov	r0, #7
	swi	SWI_LCD_CLEAR_LINE
	mov	pc, lr

ClearInput:
	mov	r0, #7
	mov	r1, #1
	ldr	r2, =Eraser
	swi	SWI_LCD_STRING

	stmfd	sp!, {lr}
	bl	PrintOperator
	ldmfd	sp!, {lr}

	mov	pc, lr

ClearTop:
	mov	r0, #7
	mov	r1, #0
	ldr	r2, =Eraser
	swi	SWI_LCD_STRING
	mov	r1, #1
	swi	SWI_LCD_STRING

	stmfd	sp!, {lr}
	bl	PrintOperator
	ldmfd	sp!, {lr}

	mov	pc, lr

ClearAll:
	mov	r0, #7
	mov	r1, #0
	ldr	r2, =Eraser
	swi	SWI_LCD_STRING
	mov	r1, #1
	swi	SWI_LCD_STRING
	mov	r1, #3
	swi	SWI_LCD_STRING

	stmfd	sp!, {lr}
	bl	PrintOperator
	bl	PrintEquals
	ldmfd	sp!, {lr}

	mov	pc, lr

PrintNumpad:
	mov	r0, #PAD_ALIGN
	mov	r1, #10
	ldr	r2, =Setup3
	swi	SWI_LCD_STRING

	mov	r1, #11
	mov	r2, #7
	swi	SWI_LCD_INT

	mov	r1, #12
	mov	r2, #4
	swi	SWI_LCD_INT

	mov	r1, #13
	mov	r2, #1
	swi	SWI_LCD_INT

	add	r0, r0, #2
	mov	r1, #11
	mov	r2, #8
	swi	SWI_LCD_INT

	mov	r1, #12
	mov	r2, #5
	swi	SWI_LCD_INT

	mov	r1, #13
	mov	r2, #2
	swi	SWI_LCD_INT

	mov	r1, #13
	mov	r2, #2
	swi	SWI_LCD_INT

	mov	r1, #14
	mov	r2, #0
	swi	SWI_LCD_INT

	add	r0, r0, #2
	mov	r1, #11
	mov	r2, #9
	swi	SWI_LCD_INT

	mov	r1, #12
	mov	r2, #6
	swi	SWI_LCD_INT

	mov	r1, #13
	mov	r2, #3
	swi	SWI_LCD_INT

	add	r0, r0, #2
	mov	r1, #11
	ldr	r3, =Signs
	add	r2, r3, #8
	swi	SWI_LCD_STRING

	mov	r1, #12
	add	r2, r3, #4
	swi	SWI_LCD_STRING

	mov	r1, #13
	add	r2, r3, #16
	swi	SWI_LCD_STRING

	mov	r1, #14
	add	r2, r3, #12
	swi	SWI_LCD_STRING

	mov	pc, lr

.data
@ contents
Total:	.word	0
Input:	.word	0
Projected:
	.word	0
	.word	0
Operation:
	.word	1
Timestamp:
	.word	0

Signs:	.word	'.', '+', '-', '×', '÷', '='

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
	.word	12	@ minus code
	.word	4
	.word	5
	.word	6
	.word	11	@ plus code
	.word	1
	.word	2
	.word	3
	.word	14	@ divide code
	.word	15	@ negative code
	.word	0
	.word	15	@ decimal code
	.word	13	@ multiply code

@ string constants
Eraser:	.asciz	"                                  "
	.align
Setup1:	.asciz	"Total:"
	.align
Setup2:	.asciz	"Input:"
	.align
Setup3:	.asciz	"Numpad:"
	.align
Instruction1:
	.asciz	"Right Button: Evalutate"
	.align
Instruction2:
	.asciz	"Left Button:"
	.align
Instruction3:
	.asciz	"Single Click: Delete"
	.align
Instruction4:
	.asciz	"Double Click: Clear"
	.align
HLine:	.asciz	"¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯"	@for 14 digit numbers
	.align

@ error messages
InvalidInput:
	.asciz	"Invalid input."
	.align
UseNumpad:
	.asciz	"Press 0-9, or operation buttons."
	.align
DivByZero:
	.asciz	"Cannot divide by zero."
	.align
