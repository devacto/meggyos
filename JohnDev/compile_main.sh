#!/bin/sh

# This is a shell script which is used to compile main.c
# main.c uses the tone library at tonelib.h and tonelib.c

# Victor Wibisono, 2012

# compiling our_screen.c into our_screen.out
avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -c our_screen.c

# compiling main.c into main.out
avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -c main.c

# linking main.out and tonelib.out
avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p our_screen.o main.o -o main

# creating main.hex, dependent on main.out and tonelib.out
avr-objcopy -O ihex -R .eeprom main main.hex

# transferring main.hex to the device
avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:main.hex
