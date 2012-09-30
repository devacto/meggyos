
// Simple Tone for the meggyjr
// Eric McCreath 2012  - GPLv3

// To compile and install:
//   avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o tone.out tone.c
//   avr-objcopy -O ihex -R .eeprom tone.out tone.hex
//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyusb0 -U flash:w:tone.hex


// For Mac OSX, change the last code to:
//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:tone.hex

#include <avr/io.h>

void delay(uint16_t ms) {
   uint16_t i,j;
   uint16_t loop = F_CPU / 17000;  
   for (i=0;i<ms;i++) {
      for (j=0;j<loop;j++);
   }
}

// beeper is connected to pin 15 which is PB1

main() {
   DDRB |= 1<<PB1;   // set pin 15 to output
   while (1) {
       PORTB |= 1<<PB1;   // set pin 15 high
       delay(8);
       PORTB &= ~(1<<PB1);   // set pin 15 low
       delay(8);
   }  
} 
