#include <msp430.h>
#include <stdio.h>

void UNHANDLED_TRAP(void *arg)
{
	// crash here
	return;
}

// int write(int fd, const void *buf, size_t count)
// {
// 	return 1;
// }

typedef void (*cb_t)(void *);
cb_t irq_callbacks[64];

int app_main(void *arg) {
	int i;
	for (i = 0; i < 64; ++i) {
		irq_callbacks[i] = UNHANDLED_TRAP;
	}

	printf("Hello, World!\n");
	P5IE |= BIT6;
	P5DIR &= ~BIT6;
	
	return 0;
}

// __attribute__((interrupt(TIMER0_A0_VECTOR))) void bloob(void)
// {

// }
