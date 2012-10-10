// Testing code for the Button Library for Meggy Jr
// Bowei Zhang, 2012

#include <avr/io.h>
#include "buttonlib.h"
#include "tonelib.h"

#define BAUD 9600
#include <util/setbaud.h>
  
void uart_init(void) {
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


main() {
    initializeButtons( );
    uart_init();

    while (1) {
        SPDR = getButtons( );
        uart_putchar('a');
        uart_putchar(':');
        uart_putchar(SPDR);
        uart_putchar('\n');
        while (!(SPSR & (1<<SPIF)));
        // Try to test if macros like BUTTONB works. Seems to be some problems
        // here...
        uart_putchar('b');
        uart_putchar( (SPDR+48) %255);
        uart_putchar('\n');
        if (SPDR & 0x3FU) {
        uart_putchar('c');
        uart_putchar(':');
        uart_putchar(SPDR);
           // PlayTone(ToneC3, 100);
            delay(0);
        }

        uart_putchar('b');
        uart_putchar(':');
        uart_putchar(SPDR);
        delay(1000);
    }
}
