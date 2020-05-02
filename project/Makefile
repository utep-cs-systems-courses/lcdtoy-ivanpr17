# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS         = -L../lib -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu={CPU} -c

all: lcdToy.elf 

#additional rules for files
lcdToy.elf: ${COMMON_OBJECTS} main.o p1_interrupt_handler.o switches.o led.o buzzer.o
	${CC} ${CFLAGS} $(LDFLAGS) -o $@ $^ -lTimer -lLcd -lShape -lCircle -lp2sw

load: lcdToy.elf
	msp430loader.sh blinkyBuzzy.elf
tidy:
	rm -f *.o *.elf *~
clean:
	rm -f *.o *.elf


