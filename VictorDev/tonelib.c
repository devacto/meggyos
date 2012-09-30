#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "tonelib.h"

void PlayTone(uint16_t tone, uint16_t duration) {
	DDRB |= 1<<PB1;
	
	uint16_t i = 0;
	
	for (i=0; i<duration; i++) {
		PORTB |= 1<<PB1;
		delay(2, tone);
		PORTB &= ~(1<<PB1);
		delay(2, tone);
	}
}


void delay(uint16_t ms, uint16_t divisor) { // the number of millisecond
	uint16_t i, j;
	uint16_t loop = F_CPU / divisor; // divisor for the tone to indicate the different pitch
	for (i=0; i<ms; i++) {
		for (j=0; j<loop; j++);
	}
}