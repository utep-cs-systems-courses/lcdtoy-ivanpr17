#ifndef switches_included
#define switches_included

#include "msp430.h"

#define SWITCHES (SW1 | SW2 | SW3 | SW4)		/* only 1 switch on this board */

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

void switch_init();
void switch_interrupt_handler();
void switch_state_machine(int state);

static unsigned char switch_state_changed;

#endif // included
