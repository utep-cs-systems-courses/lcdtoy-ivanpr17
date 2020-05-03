#include <msp430.h>
#include <libTimer.h>
#include "buzzer.h"
#include "switches.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
  configureClocks(); // sets up main oscillator, CPU & clocks
  switch_init(15);

  or_sr(0x18); // CPU off, GIE on
}
