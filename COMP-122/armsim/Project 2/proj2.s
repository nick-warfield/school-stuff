// Encryption Project

// system commands
.equ	SWI_EXIT, 0x11
.equ	SWI_OPEN, 0x66
.equ	SWI_CLOSE, 0x68
.equ	SWI_READ_STRING, 0x6a
.equ	SWI_READ_INT, 0x6c
.equ	SWI_WRITE, 0x69
.equ	SWI_ALLOCATE, 0x12
.equ	SWI_DEALLOCATE, 0x13

// file mode
.equ	StdOut, 1
.equ	StdIn, 0

.equ	MinKeyValue, 0
.equ	MaxKeyValue, 127

.global	_start

// r3 = key
// r4 = bytes in message

.text
_start:
	// open and verify command file
	ldr	r0, =CommandFile
	mov	r1, #StdIn
	swi	SWI_OPEN
	bcs	DNE_Error1

	ldr	r1, =CommandFileHandle
	str	r0, [r1]

	ldr	r0, =CommandFileHandle
	ldr	r0, [r0]
	swi	SWI_READ_INT
	bcs	Empty_Error1

	// Check if first input is 1 or 0	
	teq	r0, #0
	beq	ReadKey
	teq	r0, #1
	beq	ReadKey
	b	Invalid_Command_Error

ReadKey:
	ldr	r0, =CommandFileHandle
	ldr	r0, [r0]
	swi	SWI_READ_INT

	// verify that key is valid, then store in r3
	bcs	Invalid_Key_Error
	cmp	r0, #MaxKeyValue
	bgt	Invalid_Key_Error
	cmp	r0, #MinKeyValue
	blt	Invalid_Key_Error
	mov	r3, r0

	// close command file, then return
	ldr	r0, =CommandFileHandle
	swi	SWI_CLOSE

OpenMessage:
	// open and verify message file
	ldr	r0, =MessageFile
	mov	r1, #StdIn
	swi	SWI_OPEN
	bcs	DNE_Error2

	ldr	r1, =MessageFileHandle
	str	r0, [r1]

dynamicAllocate:
	// allocate input array
	add	r2, r2, #100
	mov	r0, r2
	ldr	r1, =inputArray
	swi	SWI_ALLOCATE
	str	r0, [r1]
	ldr	r1, [r1]

	// read file
	ldr	r0, =MessageFileHandle
	ldr	r0, [r0]
	swi	SWI_READ_STRING

	// check if entire file was not read
	teq	r0, r2
	swieq	SWI_DEALLOCATE
	beq	dynamicAllocate

	// track bytes stored and close file
	mov	r4, r0
	ldr	r0, =MessageFileHandle
	swi	SWI_CLOSE

	// allocate output array
	ldr	r1, =outputArray
	mov	r0, r4
	swi	SWI_ALLOCATE
	str	r0, [r1]

	// setup for XOR operations
	ldr	r0, =inputArray
	ldr	r0, [r0]
	ldr	r1, =outputArray
	ldr	r1, [r1]

	sub	r4, r4, #1

XOR:
	sub	r4, r4, #1

	// load a byte at a time, xor, then store result
	ldrb	r2, [r0, r4]
	eor	r2, r3, r2
	strb	r2, [r1, r4]

	teq	r4, #0
	bne	XOR

output:
	ldr	r0, =OutFile
	mov	r1, #StdOut
	swi	SWI_OPEN
	ldr	r1, =OutFileHandle
	str	r0, [r1]

	ldr	r0, =OutFileHandle
	ldr	r0, [r0]
	ldr	r1, =outputArray
	ldr	r1, [r1]

	swi	SWI_WRITE
	swi	SWI_CLOSE

Exit:	swi	SWI_DEALLOCATE
	swi	SWI_EXIT

// expects r2 to contain file name, and r3 to contain error message
Print_Error:	
	mov	r0, #StdOut
	ldr	r1, =ERROR
	swi	SWI_WRITE
	mov	r1, r2
	swi	SWI_WRITE
	mov	r1, r3
	swi	SWI_WRITE
	b	Exit

DNE_Error1:
	ldr	r2, =CommandFile
	ldr	r3, =DNE
	b	Print_Error
DNE_Error2:
	ldr	r2, =MessageFile
	ldr	r3, =DNE
	b	Print_Error
Empty_Error1:
	ldr	r0, =CommandFileHandle
	swi	SWI_CLOSE
	ldr	r2, =CommandFile
	ldr	r3, =Empty
	b	Print_Error
Empty_Error2:
	ldr	r0, =MessageFileHandle
	swi	SWI_CLOSE
	ldr	r2, =MessageFile
	ldr	r3, =Empty
	b	Print_Error
Invalid_Command_Error:
	ldr	r0, =CommandFileHandle
	swi	SWI_CLOSE
	ldr	r2, =CommandFile
	ldr	r3, =InvalidCommand
	b	Print_Error
Invalid_Key_Error:
	ldr	r0, =CommandFileHandle
	swi	SWI_CLOSE
	ldr	r2, =CommandFile
	ldr	r3, =InvalidKey
	b	Print_Error

.data
inputArray:
	.word	0
outputArray:
	.word	0

CommandFile:
	.asciz	"inputCommand.txt"
	.align
CommandFileHandle:
	.word	4
MessageFile:
	.asciz	"messageInput.txt"
	.align
MessageFileHandle:
	.word	4
OutFile:
	.asciz	"messageOutput.txt"
	.align
OutFileHandle:
	.word	4

// Error messages
ERROR:	.asciz	"ERROR: "
	.align
DNE:
	.asciz	" does not exist."
	.align
Empty:
	.asciz	" contains no data."
	.align
InvalidCommand:
	.asciz	" should begin with 0 to encrypt or 1 to decrypt."
	.align
InvalidKey:
	.asciz	" should end with a key value of at least 0 and at most 127."
	.align

