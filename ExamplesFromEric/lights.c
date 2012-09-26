
// Simple Lights for the meggyjr - turning the D0-D7 leds on and off and
// turning one row of the display leds on and off.
// Eric McCreath 2012  - GPLv3

// To compile and install:
//   avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o lights.out lights.c
//   avr-objcopy -O ihex -R .eeprom lights.out lights.hex
//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:lights.hex


// For Mac OSX, change the last code to:
//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:lights.hex

#include <avr/io.h>

void delay(uint16_t ms) {
   uint16_t i,j;
   uint16_t loop = F_CPU / 17000;  // this is approximate and needs calabration.
   for (i=0;i<ms;i++) {
      for (j=0;j<loop;j++);
   }
}

// This is a little harder than the buzzer as the tone are driven via a 
// led driver chip that takes serial input. 

main() {
   uint8_t dataLights = 0x03;
   uint8_t dataRed = 0x05;
   uint8_t dataGreen = 0x9;
   uint8_t dataBlue = 0x11;

   DDRB |=  (1<<PB2) | (1<<PB3); // make the serial pins output   
   PORTB |= (1<<PB2);  // set the led drivers to recieve input
 
   DDRD |= (1<<PD5); // make the pin for row 4 output
   PORTD &= ~(1<<PD5); // turn that row on.

   SPCR = (1 << SPE) | ( 1 << MSTR );    // enable SPI, master, and set clock rate
   while (1) {
       SPDR = dataLights; // set the shift out register
       while(!(SPSR & (1<<SPIF))); // wait until complete

       SPDR = dataRed; 
       while(!(SPSR & (1<<SPIF))); 

       SPDR = dataGreen; 
       while(!(SPSR & (1<<SPIF))); 

       SPDR = dataBlue; 
       while(!(SPSR & (1<<SPIF))); 

       delay(1000);
       dataLights = (dataLights << 1) | (dataLights >> 7);
       dataRed = (dataRed << 1) | (dataRed >> 7);
       dataGreen = (dataGreen << 1) | (dataGreen >> 7);
       dataBlue = (dataBlue << 1) | (dataBlue >> 7);
    }
} 
