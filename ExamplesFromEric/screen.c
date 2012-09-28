
// Simple Screen for the meggyjr - draw the screen from a frame buffer. 
// Eric McCreath 2012  - GLPv3

// To compile and install:
//   avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o screen.out screen.c
//   avr-objcopy -O ihex -R .eeprom screen.out screen.hex
//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:screen.hex


#include <avr/io.h>

uint8_t fbRed[8];
uint8_t fbGreen[8];
uint8_t fbBlue[8];
uint8_t fbLights;


void delay(uint16_t ms) {
   uint16_t i,j;
   uint16_t loop = F_CPU / 17000;  // this is approximate and needs calabration.
   for (i=0;i<ms;i++) {
      for (j=0;j<loop;j++);
   }
}

void initFrameBuffer() {
   DDRB |=  (1<<PB2) | (1<<PB3); // make the serial pins output   
   PORTB |= (1<<PB2);  // set the led drivers to recieve input
 
   DDRD |= (1<<PD2); // make the pin for row 0 output
   PORTD |= (1<<PD2); // turn that row off.

   DDRD |= (1<<PD3); // row 2
   PORTD |= (1<<PD3); 

   DDRD |= (1<<PD4); // row 3
   PORTD |= (1<<PD4); 
  
   DDRD |= (1<<PD5); // row 4
   PORTD |= (1<<PD5); 

   DDRD |= (1<<PD6); // row 5
   PORTD |= (1<<PD6); 

   DDRD |= (1<<PD7); // row 6
   PORTD |= (1<<PD7); 

   DDRB |= (1<<PB0); // row 7
   PORTB |= (1<<PB0); 

   DDRB |= (1<<PB4); // row 8
   PORTB |= (1<<PB4); 
}

void drawFrameBuffer() {
     uint8_t i;
     
     for (i=1;i<=8;i++) {
        
       SPCR = (1 << SPE) | ( 1 << MSTR );    // enable SPI, master, and set clock rate

        SPDR = fbLights; // set the shift out register
        while(!(SPSR & (1<<SPIF))); // wait until complete

        SPDR = fbRed[i-1]; 
        while(!(SPSR & (1<<SPIF))); 

        SPDR = fbGreen[i-1]; 
        while(!(SPSR & (1<<SPIF))); 

        SPDR = fbBlue[i-1]; 
        while(!(SPSR & (1<<SPIF))); 
        SPCR = 0; //turn off spi 


        if (i==1) {
            PORTD &= ~(1<<PD2);
        } else if (i==2) {
            PORTD &= ~(1<<PD3);
        } else if (i==3) {
            PORTD &= ~(1<<PD4);
        } else if (i==4) {
            PORTD &= ~(1<<PD5);
        } else if (i==5) {
            PORTD &= ~(1<<PD6);
        } else if (i==6) {
            PORTD &= ~(1<<PD7);
        } else if (i==7) {
            PORTB &= ~(1<<PB0);
        } else if (i==8) {
            PORTB &= ~(1<<PB4);
        }

        delay(1);

        if (i==1) {
            PORTD |= (1<<PD2);
        } else if (i==2) {
            PORTD |= (1<<PD3);
        } else if (i==3) {
            PORTD |= (1<<PD4);
        } else if (i==4) {
            PORTD |= (1<<PD5);
        } else if (i==5) {
            PORTD |= (1<<PD6);
        } else if (i==6) {
            PORTD |= (1<<PD7);
        } else if (i==7) {
            PORTB |= (1<<PB0);
        } else if (i==8) {
            PORTB |= (1<<PB4);
        }
     }
}


main() {
   initFrameBuffer();
   fbLights = 0xAAU;
   fbRed[0] = 0x08U;
   fbGreen[1] = 0xFFU;
   fbBlue[2] = 0x11U;
   fbRed[3] = 0x80U;
   fbRed[4] = 0x40U;
   fbRed[5] = 0x20U;
   fbRed[6] = 0x10U;
   fbRed[7] = 0xAAU;

   while (1) {
      drawFrameBuffer();
   }
} 
