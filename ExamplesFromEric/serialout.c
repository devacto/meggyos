
// Simple serial output for the meggyjr
// Eric McCreath 2012  - GPLv3

// To compile and install:
//   avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o serialout.out serialout.c
//   avr-objcopy -O ihex -R .eeprom serialout.out serialout.hex
//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:serialout.hex
// to connect to the output:
//    minicom -b 9600 -D /dev/ttyUSB0

//   avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:serialout.hex


#include <avr/io.h>

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
   uart_init();
   while(1) {
      uart_putchar('h');
      uart_putchar('e');
      uart_putchar('l');
      uart_putchar('l');
      uart_putchar('o');
   }
} 
