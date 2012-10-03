#include <avr/io.h>

void initializeButtons( )
{
   DDRB |=  (1<<PB2) | (1<<PB3); // make the serial pins output   
   PORTB |= (1<<PB2);  // set the led drivers to recieve input
 
   SPCR = (1 << SPE) | ( 1 << MSTR );    // enable SPI, master, and set clock rate

           
   PORTC = 255U;   // Set port c as pull ups
   DDRC = 0;       // Set port c as all inputs
}

uint8_t getButtons( )
{
    return (~(PINC) & 0x3FU);
}

void delay(uint16_t ms) 
{
    uint16_t i, j;
    uint16_t loop = F_CPU / 17000;

    for (i = 0; i < ms; ++i) {
        for (j = 0; j < loop; ++j) {
        }
    }
}
