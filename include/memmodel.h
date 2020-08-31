#ifndef MEMMODEL_H_
#define MEMMODEL_H_

#ifdef __ASSEMBLER__
	#ifdef __MSP430X_LARGE__
		#define _pushm 	pushm.a
		#define _popm 	popm.a

		#define _push 	push.a 
		#define _pop 	pop.a


		#define _mov 	mova 
		#define _movx 	movx 

		#define _add 	adda
		#define _sub 	suba
		#define _cmp	cmpa

		#define _call 	calla 
		#define _ret 	reta
		#define _br 	bra

		#define _ptrsz 4
	#else
		#define _pushm 	pushm.w
		#define _popm 	popm.w

		#define _push 	push.w 
		#define _pop 	pop.w


		#define _mov 	mov.w 

		#define _add 	add.w
		#define _sub 	sub.w
		#define _cmp	cmp.w

		#define _call 	call 
		#define _ret 	ret
		#define _br 	br

		#define _ptrsz 	2
	#endif
#endif

#endif