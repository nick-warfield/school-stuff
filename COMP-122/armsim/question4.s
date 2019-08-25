Main:
	LDR	r0, =DataTable
	LDR	r1, =Value
	LDRB	r1, [r1]
	MOV	r1, r1, lsl #0x2
	ADD	r0, r0, r1
	LDR	r2, [r0]
	LDR	r3, =Result
	STR	r2, [r3]
	SWI	#0x11

.Data
DataTable:
	.word	1
	.word	1
	.word	2
	.word	6
	.word	24
	.word	120
	.word	720
	.word	5040
	.word	40320

Value:	.byte	6
	.align

Result:	.word	0

.END
