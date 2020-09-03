;-------------------------------------------------------------------------------
; includes
;-------------------------------------------------------------------------------

		#include "msp430.h"
		#include "utils.h"
		#include "memmodel.h"

;-------------------------------------------------------------------------------
; defines
;-------------------------------------------------------------------------------
	
		#define INTPRE_(inum) JOIN(__irq_pre_, DEPAREN(inum))

		#define INTCB_(inum) JOIN(__irq_cb_, DEPAREN(inum))

		#define CB_(inum) JOIN(cb_, DEPAREN(inum))

		#define INTPOST_(inum) JOIN(__irq_post_, DEPAREN(inum))

		#define INTNAME_(inum) JOIN(__interrupt_vector_, DEPAREN(inum))

		#define INTTBLOFFS_(inum) (_ptrsz * inum)

		#define MSP430_MAX_INTVECS 64

.macro __save_ctx
		#if defined(__MSP430_HAS_MSP430XV2_CPU__) || \
			defined(__MSP430_HAS_MSP430X_CPU__)
			_pushm #12, r15
		#else
			_push r15
			_push r14
			_push r13
			_push r12
			_push r11
			_push r10
			_push r9
			_push r8
			_push r7
			_push r6
			_push r5
			_push r4
		#endif
.endm

.macro __restore_ctx
		#if defined(__MSP430_HAS_MSP430XV2_CPU__) || \
			defined(__MSP430_HAS_MSP430X_CPU__)
			_popm #12, r15
		#else
			_pop r4
			_pop r5
			_pop r6
			_pop r7
			_pop r8
			_pop r9
			_pop r10
			_pop r11
			_pop r12
			_pop r13
			_pop r14
			_pop r15
		#endif
.endm

.macro __gen_body inum
	.weak INTPRE_(\inum)
	.type INTPRE_(\inum), @function

	.set inttbloffs, INTTBLOFFS_(\inum)

	INTPRE_(\inum):
			__save_ctx

	INTCB_(\inum):
			_mov #irq_callbacks, r12
			_mov inttbloffs(r12), r13
			_call r13

	INTPOST_(\inum):
			__restore_ctx
			nop
			reti

	.size INTPRE_(\inum), .-INTPRE_(\inum)
.endm

.macro __gen_linkage inum
		.sect INTNAME_(\inum), "ax", @progbits
		.word INTPRE_(\inum)
.endm

;-------------------------------------------------------------------------------
; MSP430 interrupt table declaration
;-------------------------------------------------------------------------------
		.data
		.global irq_callbacks
		.sect .handlers, "a", @progbits
		.type irq_callbacks, @object


		.altmacro		
		.set i, 0
		.rept MSP430_MAX_INTVECS
			__gen_body %i
			.set i, i+1
		.endr

		.altmacro		
		.set i, 0
		.rept MSP430_MAX_INTVECS
			__gen_linkage %i
			.set i, i+1
		.endr

		.end
	
