#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "tonelib.h"

void PlayTone() {
	DDRB |= 1<<PB1;
	while(1) {
		PORTB |= 1<<PB1;
		delay(2);
		PORTB &= ~(1<<PB1);
		delay(2);
	}
}


void delay(uint16_t ms) { // the number of millisecond
	uint16_t i, j;
	uint16_t loop = F_CPU / 61157; // constant is divisor for the tone
	for (i=0; i<ms; i++) {
		for (j=0; j<loop; j++);
	}
}