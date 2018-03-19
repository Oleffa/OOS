#include <system.h>

// How many ticks passed (uptime)
int timer_ticks = 0;

void timer_handler(struct regs *r)
{
	// Increment tick count
	timer_ticks++;

	// Every 18 clocks = 1 second dislay something
	if (timer_ticks % 18 == 0)
	{
		k_printf("One second has passed\n");
	}
}

void timer_install()
{
	//Install the timer handler to IRQ0
	irq_install_handler(0, timer_handler);
}
