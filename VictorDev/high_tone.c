
// High Tone for the meggyjr
// Victor Hartanto Wibisono 2012
// modified from code by Eric McCreath 2012

// To compile and install:
//		avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o high_tone.out high_tone.c
//		avr-objcopy -O ihex -R .eeprom high_tone.out high_tone.hex
//		avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:high_tone.hex
		
#include <avr/io.h>

void delay(uint16_t ms) { // the number of millisecond
	uint16_t i, j;
	uint16_t loop = F_CPU / 61157; // what is F_CPU? That is the cpu 16 MHz clock
	for (i=0; i<ms; i++) {
		for (j=0; j<loop; j++);
	}
}

// beeper is connected to pin 15 which is PB1
// beeper register is OC1A

main() {
	DDRB |= 1<<PB1;
	while(1) {
		PORTB |= 1<<PB1;
		delay(2);
		PORTB &= ~(1<<PB1);
		delay(2);
	}
}		