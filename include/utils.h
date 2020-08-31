#ifndef UTILS_H_
#define UTILS_H_

/********************************************************************************
 * includes
 ********************************************************************************/
#ifndef __ASSEMBLER__
	#if (__STDC_VERSION__ == 201112L)
		#include <assert.h>
	#endif /* __STDC_VERSION__ == 201112L */

	#include <stdbool.h>
	#include <stdint.h>
#endif

/********************************************************************************
 * macros and constant definitions
 ********************************************************************************/
#define STR_(x) 						#x
#define STR(x) 							STR_(x)

#define JOIN_(x, y) 					x##y
#define JOIN(x, y) 						JOIN_(x, y)

#define DEPAREN(X) ESC(ISH X)
#define ISH(...) ISH __VA_ARGS__
#define ESC(...) ESC_(__VA_ARGS__)
#define ESC_(...) VAN ## __VA_ARGS__
#define VANISH

#if !defined(static_assert)
	#define STATIC_ASSERT_SIG_(msg) 	JOIN(STATIC_ASSERTION_, msg)
	#define STATIC_ASSERT_VAL_(expr) 	(2 * (!!(expr)) - 1)

	#define STATIC_ASSERT_MSG_(expr, msg) \
		typedef char \
		STATIC_ASSERT_SIG_(msg) \
		[STATIC_ASSERT_VAL_(expr)]

	#define STATIC_ASSERT_LINE_(expr, line) \
		STATIC_ASSERT_MSG_( \
			expr, \
			JOIN(AT_LINE_, line) \
		)			

	#define STATIC_ASSERT_NOARGS_(expr, line) \
		STATIC_ASSERT_LINE_(expr, line)

	#define STATIC_ASSERT_(expr) \
		STATIC_ASSERT_NOARGS_(expr, __LINE__)

	#define STATIC_ASSERT_DISPATCH_(_1, _2, _FUNC, ...) \
		_FUNC

	#define STATIC_ASSERT(...) \
		STATIC_ASSERT_DISPATCH_( \
			__VA_ARGS__, \
			STATIC_ASSERT_MSG_, \
			STATIC_ASSERT_ \
		)(__VA_ARGS__)						

#else
	#define STATIC_ASSERT(...) do { static_assert(...) } while (0)
#endif /* !defined(static_assert) */

#define VAR_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N

#define VAR_NARG_(...) VAR_ARG_N(__VA_ARGS__)

#define VAR_RSEQ_N() \
	100, 99, 98, 97, 96, 95, 94, 93, 92, 91,	\
	 90, 89, 88, 87, 86, 85, 84, 83, 82, 81,	\
	 80, 79, 78, 77, 76, 75, 74, 73, 72, 71,	\
	 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 	\
	 60, 59, 58, 57, 56, 55, 54, 53, 52, 51,	\
	 50, 49, 48, 47, 46, 45, 44, 43, 42, 41,	\
	 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,	\
	 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,	\
	 20, 19, 18, 17, 16, 15, 14, 13, 12, 11,	\
	 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0


#define VAR_NARG(...) VAR_NARG_(__VA_ARGS__, VAR_RSEQ_N())

#define MATH_MOD(a, b)                 (((a % b) + b) % b)

#define IS_POW2(n)                     ((n) & ((n) - 1))

#define ARRAY_SIZEOF(x) \
	(sizeof(x) / sizeof(x[0]))

#define ARRAY_BASE(ptr, type, offset) \
	((char *)(ptr)) - ((sizeof(type)) * offset)

#define OFFSET_OF(type, field) (size_t)(&((type *)(0))->field)

#define CONTAINER_OF(ptr, type, field) \
        ((type *)(((char *)(ptr)) - OFFSET_OF(type, field)))
		
/********************************************************************************
 * globals
 ********************************************************************************/

/********************************************************************************
 * locals
 ********************************************************************************/

/********************************************************************************
 * function prototypes
 ********************************************************************************/

// coding style:
// booleans will NOT be tested the same as nonbooleans
// operators will always have the target on the LEFT and the value on the right
// 80 character maximum width
// conditional compile of dprintf

#endif