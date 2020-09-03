#include <msp430.h>
#include <boot.h>

extern int app_main(void *arg);

int main(void)
{
	// initialize bsp
	// initialize debug utilities

	// print out some useful stuff
	// boot kernel while printing stuff out
	(void) app_main(0);
	return 0;
}

// bsp needs flexible RAW and scheduled interrupts setup
// bsp
// debug
// port
