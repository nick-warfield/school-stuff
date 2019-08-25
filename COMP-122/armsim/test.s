	mov	r3, #100
	mov	r0, #50
@	mov	r1, #49
	mov	r1, #51

loop:
	cmp	r0, r1

	moveq	r3, #0
	movne	r3, #1
	movhs	r3, #2
	movlo	r3, #3
	movmi	r3, #4
	movpl	r3, #5
	movvs	r3, #6
	movvc	r3, #7
	movhi	r3, #8
	movls	r3, #9

	adds	r3, r3, #0
	b	loop
