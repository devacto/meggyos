/*
 *
 * This is the screen function for our project
 * COMP3300 Group 20
 *
 */

#include "our_screen.h"

extern uint8_t fbRed[];
extern uint8_t fbGreen[];
extern uint8_t fbBlue[];
extern uint8_t fbLights;



void delay(uint16_t ms) {
   uint16_t i,j;
   uint16_t loop = F_CPU / 17000;  // this is approximate and needs calabration.
   for (i=0;i<ms;i++) {
      for (j=0;j<loop;j++);
   }
}



void turnOnFrameBuffer() {
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
        
        // turn on SPI and make current as master chip,
        // transfer data to the buffer
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

        // turn on that line so that the leds on that line will show based on 
        // the RGB 3 bytes data in that buffer
        //
        // if we leave the door open for line, that line will show the colour
        // based on the current data in the buffer
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

        // turn off the line, so it won't be disturbed by next data in the buffer
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



#ifdef USE_MAIN
int main()
{
    fbLights = 0xAAU;
    fbRed[0] = 0x08U;
    fbGreen[1] = 0xFFU;
    fbBlue[2] = 0x11U;
    fbRed[3] = 0x80U;
    fbRed[4] = 0x40U;
    fbRed[5] = 0x20U;
    fbRed[6] = 0x10U;
    fbRed[7] = 0xAAU;

    drawFrameBuffer(1, 1)
}
#endif
