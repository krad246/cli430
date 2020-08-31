;-------------------------------------------------------------------------------
; MS-TOS MSP430 boot code
;-------------------------------------------------------------------------------
            
		#include "msp430.h"
		#include "memmodel.h"

;-------------------------------------------------------------------------------
            
		.text                           
		.global _start					
		.global main

;-------------------------------------------------------------------------------

_start:      
		_mov  	#__stack, sp					; initialize stack pointer

		;-------------------

		dint									; enter critical section
		nop

		;-------------------

		_mov	#(WDTPW | WDTHOLD), &WDTCTL 	; freeze watchdog
		
		;-------------------

		_mov	#__bssstart, r12			 
		clr.w	r13
		_mov	#__bsssize, r14

	.ifdef __MSP430X_LARGE__
		clr.w	R15									
	.endif

		_call	#memset							; zero-init .bss

		;-------------------

		_mov	#__datastart, r12
		_mov	#__romdatastart, r14

		_cmp	r12, r13						; skip if no memory
												; needs to be moved
		jeq		_call_main
		_mov	#__romdatacopysize, r14
	
	.ifdef __MSP430X_LARGE__
		clr.w	R15									
	.endif

		_call	#memmove						; copy rom to ram

		;-------------------

_call_main:; Set argc == 0
		clr.w	R12									
		_call	#main

_main_exit:
		bis.w	#LPM3_bits,	sr
		nop

		jmp		_main_exit

;-------------------------------------------------------------------------------
;           stack pointer definition
;-------------------------------------------------------------------------------

        .sect 	.stack

;-------------------------------------------------------------------------------
;           interrupt vectors
;-------------------------------------------------------------------------------
        .sect   .resetvec, "ax", @progbits            
        .word  	_start

		.end
