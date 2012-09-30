
// Using an interrupt to generate a tone. 
// Eric McCreath 2012  - GPLv3

// To compile and install:
//   avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o interrupt.out interrupt.c
//   avr-objcopy -O ihex -R .eeprom interrupt.out interrupt.hex
//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:interrupt.hex

//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:interrupt.hex

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

main() {
   DDRB |= 1<<PB1;   // set pin 15 to output
   
   TCCR2A = (1<<WGM21); // clear timer on compare match
   TCCR2B = (1<<CS21);  // timer uses main system clock with 1/8 prescale
   OCR2A  = 100; 
   TIMSK2 = (1<<OCIE2A); // call interrupt on output compare match

   sei( );    // Enable interrupts

   while (1) {
   }  
} 

SIGNAL(TIMER2_COMPA_vect)
{
   if (PORTB & 1<<PB1) {
      PORTB &= ~(1<<PB1);   // set pin 15 low
   } else {
      PORTB |= 1<<PB1;   // set pin 15 high
   }
}

