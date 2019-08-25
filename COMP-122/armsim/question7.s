.text
@ initialize variables
	ldr	r0, =a
	mov	r1, #3
	str	r1, [r0]
	ldr	r0, =b
	mov	r1, #5
	str	r1, [r0]
	ldr	r0, =c
	mov	r1, #4
	str	r1, [r0]
	ldr	r0, =d
	mov	r1, #4
	str	r1, [r0]
	ldr	r0, =e
	mov	r1, #2
	str	r1, [r0]
	ldr	r0, =x
	mov	r1, #0
	str	r1, [r0]

@ addAll
	ldr	r0, =a
	ldr	r0, [r0]
	ldr	r1, =b
	ldr	r1, [r1]
	add	r0, r0, r1
	ldr	r1, =c
	ldr	r1, [r1]
	add	r0, r0, r1
	ldr	r1, =d
	ldr	r1, [r1]
	add	r0, r0, r1
	ldr	r1, =e
	ldr	r1, [r1]
	add	r0, r0, r1

@ store result
	ldr	r1, =x
	str	r0, [r1]
	swi	#0x11

.data
a:	.word	0	
b:	.word	0	
c:	.word	0	
d:	.word	0	
e:	.word	0	
x:	.word	0	
