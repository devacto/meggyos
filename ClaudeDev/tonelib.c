#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "tonelib.h"

void PlayTone(uint16_t tone, uint16_t duration) {
	DDRB |= 1<<PB1;
	
	uint16_t i;
	
	for (i=0; i<duration; i++) {
		PORTB |= 1<<PB1;
		delay(2, tone);
		PORTB &= ~(1<<PB1);
		delay(2, tone);
	}
}
