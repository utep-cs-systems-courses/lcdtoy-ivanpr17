#include <msp430.h>
#include <libTimer.h>
#include "buzzer.h"
#include "switches.h"
#include <stdio.h>
#include <stdlib.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <shape.h>
#include <abCircle.h>
#include "shapemotion.h"

int main(void){
  
  configureClocks(); // sets up main oscillator, CPU & clocks
  switch_init(15);
  lcd_init();
  setScreen();
  

  or_sr(0x8); // CPU off, GIE on
}
