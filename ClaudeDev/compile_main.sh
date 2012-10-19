#!/bin/sh

# This is a shell script which is used to compile main.c
# main.c uses the tone library at tonelib.h and tonelib.c

# Claude Zhang, 2012
# John Weng, 2012
# Victor Wibisono, 2012

# compiling tonelib.c into tonelib.o
avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -c meggyLibrary.c

avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -c gameLibrary.c
# compiling main.c into main.o
avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -c multithreading.c

# linking main.o and tonelib.o into main
avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p meggyLibrary.o gameLibrary.o multithreading.o -o multithreading

# creating main.hex from main
avr-objcopy -O ihex -R .eeprom multithreading multithreading.hex

# transferring main.hex to the device
avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:multithreading.hex
