#include <msp430.h>
#include "switches.h"
#include "buzzer.h"
#include <libTimer.h>

// To avoid implicit declaration warning
void ZeldaTheme();
void ZeldaItem();

static unsigned char switches_current, switch_state_changed, switch_mask, switches_last_reported;
int state = 0;

static void switch_update_interrupt_sense(){
  switches_current = P2IN & switch_mask;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (switches_current);	/* if switch up, sense down */
  P2IES &= (switches_current | ~switch_mask);	/* if switch down, sense up */
}


void switch_init(unsigned char mask){/* setup switch */
  switch_mask = mask;
  P2REN |= mask;		/* enables resistors for switches */
  P2IE = mask;		/* enable interrupts from switches */
  P2OUT |= mask;		/* pull-ups for switches */
  P2DIR &= ~mask;           /* set switches' bits for input */
  
  switch_update_interrupt_sense();
}

unsigned int p2sw_read(){
  unsigned int sw_changed = switches_current ^ switches_last_reported;
  switches_last_reported = switches_current;
  return switches_current | (sw_changed << 8);
}


void switch_interrupt_handler(){
  if(switch_state_changed){
    unsigned int switches = p2sw_read(), i;
    char str[5];
    for(i=0; i<4; i++)
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;
    str[4] = 0;
  
    //if statements for when a switch is up
    if(str[0] != '-'){
      state = 01;
      switch_state_machine(state);
    }
    else if(str[1] != '-'){
      state = 02;
      switch_state_machine(state);
    }
    else if(str[2] != '-'){
      state = 03;
      switch_state_machine(state);
    }
    else if(str[3] != '-'){
      state = 04;
      switch_state_machine(state);
    }
    switch_state_changed = 0;
  }
}

void switch_state_machine(int state){
  //if switch is pressed, below code determines proper case
  switch(state){
  case 01:// Plays part of Zelda Theme and shines LEDs
    switch_state_changed = 1;
    ZeldaTheme();
    
    break;
  case 02:// Shines LEDs
    switch_state_changed = 1;
    
    
    break;
  case 03://Plays Zelda Item tune and shines LEDs
    switch_state_changed = 1;
    ZeldaItem();

    break;
  case 04://Plays Zelda Item tune
    switch_state_changed = 1;
    ZeldaItem();

    break;

  default:

    break;
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & switch_mask){
    P2IFG &= ~switch_mask;
    switch_state_changed = 1;
    switch_update_interrupt_sense();
    switch_interrupt_handler();
  }
}
