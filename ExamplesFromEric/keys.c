
// Key input for the meggyjr - turning the D0-D7 leds on and off 
// based on the key presses.
// Eric McCreath 2012  - GPLv3

// To compile and install:
//   avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o keys.out keys.c
//   avr-objcopy -O ihex -R .eeprom keys.out keys.hex
//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:keys.hex

//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:keys.hex

#include <avr/io.h>

void delay(uint16_t ms) {
   uint16_t i,j;
   uint16_t loop = F_CPU / 17000;  // this is approximate and needs calabration.
   for (i=0;i<ms;i++) {
      for (j=0;j<loop;j++);
   }
}

// This is a little harder than the buzzer as the leds are driven via a 
// led driver chip that takes serial input. 

main() {
   uint8_t dataLights = 0x00;
   uint8_t dataRed = 0x00;
   uint8_t dataGreen = 0x00;
   uint8_t dataBlue = 0x00;

   DDRB |=  (1<<PB2) | (1<<PB3); // make the serial pins output   
   PORTB |= (1<<PB2);  // set the led drivers to recieve input
 
   SPCR = (1 << SPE) | ( 1 << MSTR );    // enable SPI, master, and set clock rate

           
   PORTC = 255U;   // Set port c as pull ups
   DDRC = 0;       // Set port c as all inputs


   while (1) {
       SPDR = (~(PINC));// & 0x3FU); // read pins on port c and set the shift out register
       while(!(SPSR & (1<<SPIF))); // wait until complete
/*
       SPDR = dataRed; 
       while(!(SPSR & (1<<SPIF))); 

       SPDR = dataGreen; 
       while(!(SPSR & (1<<SPIF))); 

       SPDR = dataBlue; 
       while(!(SPSR & (1<<SPIF))); 

       */
       delay(1);
    }
} 
