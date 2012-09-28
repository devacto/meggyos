
// Scribble program for the meggyjr - arrows move a pen 
// around the screen and draw as it goes. Right buttons cycle 
// the colour.
// Eric McCreath 2012  - GPLv3

// To compile and install:
//   avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o scribble.out scribble.c
//   avr-objcopy -O ihex -R .eeprom scribble.out scribble.hex
//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:scribble.hex


#include <avr/io.h>

uint8_t fbRed[8];
uint8_t fbGreen[8];
uint8_t fbBlue[8];
uint8_t fbLights;

struct peninfo {
    uint8_t x,y;
    uint8_t c; // color 0 - clear or no change, 
               //       1 - red, 2 - blue, 3 - green
               //       4 - remove colour
};
struct peninfo pen;

void drawpen() {
   if (pen.c == 1) {
      fbRed[pen.y] |= 1<<pen.x;
   } else   if (pen.c == 2) {
      fbBlue[pen.y] |= 1<<pen.x;
   } else   if (pen.c == 3) {
      fbGreen[pen.y] |= 1<<pen.x;
   } else   if (pen.c == 4) {
      fbRed[pen.y] &= ~(1<<pen.x);
      fbBlue[pen.y] &= ~(1<<pen.x);
      fbGreen[pen.y] &= ~(1<<pen.x);
   } 
}


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
 
   DDRD |= (1<<PD2); // make the pin for row 1 output
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
        SPCR = 0;


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
   PORTC = 255U;   // Set port c as pull ups
   DDRC = 0;       // Set port c as all inputs

   initFrameBuffer();
  
   pen.x = 3;
   pen.y = 3;
   pen.c = 1;

   uint16_t cursorcount = 0;
   uint8_t cursorRed;
   uint8_t cursorGreen;
   uint8_t cursorBlue;
  
   uint8_t lastc, nextc;
   lastc = (~(PINC) & 0x3FU); 

   while (1) {
      nextc = (~(PINC) & 0x3FU); 
      if (nextc & (1<<2) & ~(lastc & (1<<2))) { // move up
         pen.x = (pen.x + 1)%8;
         drawpen();
      } else if (nextc & (1<<3) & ~(lastc & (1<<3))) { // move down
         pen.x = (pen.x - 1)%8;
         drawpen();
      } else if (nextc & (1<<5) & ~(lastc & (1<<5))) { // move right
         pen.y = (pen.y - 1)%8;
         drawpen();
      } else if (nextc & (1<<4) & ~(lastc & (1<<4))) { // move left
         pen.y = (pen.y + 1)%8;
         drawpen();
      } else if (nextc & (1<<1) & ~(lastc & (1<<1))) { // 
         pen.c = (pen.c + 1)%5;
      } else if (nextc & (1<<0) & ~(lastc & (1<<0))) { // 
         pen.c = (pen.c + 4)%5;

      } 
      fbLights = 1<<pen.c;

      if (cursorcount > 30) {  // make the pixel under the cursor white(and record the colour that was there)
         cursorRed = fbRed[pen.y] & 1<<pen.x;
         cursorGreen = fbGreen[pen.y] & 1<<pen.x;
         cursorBlue = fbBlue[pen.y] & 1<<pen.x;
         fbGreen[pen.y] |= 1<<pen.x;
         fbBlue[pen.y] |= 1<<pen.x;
         fbRed[pen.y] |= 1<<pen.x;           
      }
      drawFrameBuffer();
      if (cursorcount > 30) { // return the previous color
          fbRed[pen.y] = (fbRed[pen.y] & ~(1<<pen.x)) | cursorRed;   
          fbGreen[pen.y] = (fbGreen[pen.y] & ~(1<<pen.x)) | cursorGreen;     
          fbBlue[pen.y] = (fbBlue[pen.y] & ~(1<<pen.x)) | cursorBlue;         
      }
      cursorcount++;
      if (cursorcount > 60) cursorcount =0;
      lastc = nextc;
   }
} 
