/********************************************************************************
 * Name:
 * Author:
 * Description:
 ********************************************************************************/

#ifndef DEBUG_H_
#define DEBUG_H_

/********************************************************************************
 * includes
 ********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <utils.h>

/********************************************************************************
 * macros and constant definitions
 ********************************************************************************/
#define DBG_OFF
#define DBG_A
#define DBG_E
#define DBG_W
#define DBG_N
#define DBG_D
#define DBG_I

#define DBG_BLACK	"\033[30m"
#define DBG_RED 	"\033[31m"
#define DBG_GREEN 	"\033[32m"
#define DBG_YELLOW 	"\033[33m"
#define DBG_BLUE 	"\033[34m"
#define DBG_MAGENTA "\033[35m"
#define DBG_CYAN	"\033[36m"
#define DBG_WHITE	"\033[37m"
#define DBG_RESET 	"\033[0m"

#if !defined(DBG_STATIC) && !defined(DBG_DYNAMIC)
#else
// define wrap_putc and wrap_puts in bsp
#endif

#ifdef DBG_STATIC
#endif

#ifdef DBG_DYNAMIC
#endif

#define PRINTF(args...) do { printf(args); } while (0)

// print color, module, message based on level
#define DPRINTF(args...)

/********************************************************************************
 * data structures
 ********************************************************************************/
struct dbg_global 
{
	// debug fifo if OS - thread synchronized
	// debug task if OS
	
	// debug level / priority
	//
};

/********************************************************************************
 * globals
 ********************************************************************************/
struct dbg_global dbg_g;

/********************************************************************************
 * function prototypes
 ********************************************************************************/

#endif /* DEBUG_H_ */