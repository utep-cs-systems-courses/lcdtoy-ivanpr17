
#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

// To avoid implicit declaration warning
void ZeldaTheme();
void ZeldaItem();

static unsigned char switches_current, switch_state_changed;

int state =0;

static void switch_update_interrupt_sense(){
  switches_current = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (switches_current);	/* if switch up, sense down */
  P2IES &= (switches_current | ~SWITCHES);	/* if switch down, sense up */
}

void switch_init()			/* setup switch */{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;           /* set switches' bits for input */
  
  switch_update_interrupt_sense();
}

unsigned int p2sw_read(){
  return switches_current;
}

void switch_interrupt_handler(){
  if(switch_state_changed){
    char p2val = p2sw_read();
  
    //if statements for when a switch is up
    if(p2val & SW1 ? 0 : 1){
      state = 01;
      switch_state_machine(state);
    }
    if(p2val & SW2 ? 0:1){
      state = 02;
      switch_state_machine(state);
    }
    if(p2val & SW3 ? 0:1){
      state = 03;
      switch_state_machine(state);
    }
    if(p2val & SW4 ? 0:1){
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
    blinkLEDS();
    ZeldaTheme();
    
    break;
  case 02:// Shines LEDs
    switch_state_changed = 1;
    blinkLEDS();
    
    
    break;
  case 03://Plays Zelda Item tune and shines LEDs
    switch_state_changed = 1;
    blinkLEDS();
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
  if (P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_state_changed = 1;
    switch_update_interrupt_sense();
    switch_interrupt_handler();
  }
}
