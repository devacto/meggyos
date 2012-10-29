#!/bin/sh

avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -c gameLibrary.c
avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -c meggyLibrary.c

avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -c main.c

avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p gameLibrary.o meggyLibrary.o main.o -o main

avr-objcopy -O ihex -R .eeprom main main.hex

avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:main.hex

minicom -b 9600 -D /dev/tty.usbserial-A501JU54
