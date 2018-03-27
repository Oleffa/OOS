#include "include/system.h"
#include "include/console.h"


void timer_handler(struct regs *r) {
	
	/* Increment our 'tick count' */
	timer_ticks++;

	/* Every 18 clocks (approximately 1 second), we will
	*  display a message on the screen */
	if (timer_ticks % 18 == 0) {
//		k_printf("One second has passed\n");
	}
}

void timer_wait(int ticks) {
	unsigned long eticks;

	eticks = timer_ticks + ticks;
	while (timer_ticks < eticks)
		;
}

void timer_install() {
	timer_ticks = 0;
	irq_install_handler(0, timer_handler); 
}
