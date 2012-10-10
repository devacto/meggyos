// Library implementation of 

#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "library.h"

// Extern variables below which will be global variables on all the files

extern uint8_t fbRed[];
extern uint8_t fbGreen[];
extern uint8_t fbBlue[];
extern uint8_t fbLights;

void PlayTone(uint16_t tone, uint16_t duration) {
	DDRB |= 1<<PB1;
	
	uint16_t i;
	
	for (i=0; i<duration; i++) {
		PORTB |= 1<<PB1;
		tone_delay(2, tone);
		PORTB &= ~(1<<PB1);
		tone_delay(2, tone);
	}
}


void tone_delay(uint16_t ms, uint16_t divisor) { // the number of millisecond
	uint16_t i, j;
	uint16_t loop = F_CPU / divisor; // divisor for the tone to indicate the different pitch
	for (i=0; i<ms; i++) {
		for (j=0; j<loop; j++);
	}
}

void delay(uint16_t ms) {
   uint16_t i,j;
   uint16_t loop = F_CPU / 17000;  // this is approximate and needs calabration.
   for (i=0;i<ms;i++) {
      for (j=0;j<loop;j++);
   }
}

// Below are methods for screen drawing

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

// Implementation of the button methods

void initializeButtons()
{
   DDRB |=  (1<<PB2) | (1<<PB3); // make the serial pins output   
   PORTB |= (1<<PB2);  // set the led drivers to recieve input
 
   SPCR = (1 << SPE) | ( 1 << MSTR );    // enable SPI, master, and set clock rate

           
   PORTC = 255U;   // Set port c as pull ups
   DDRC = 0;       // Set port c as all inputs
}

uint8_t getButtons()
{
    return (~(PINC) & 0x3FU);
}

// Implementation of serial-out methods 

void uart_init() {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    UCSR0A &= ~(_BV(U2X0));

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */ 
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

void uart_putchar(char c) {
    loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
    UDR0 = c;
}