#!/bin/sh

# This is a shell script which is used to compile high_tone.c
# Victor Wibisono, 2012

avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o high_tone.out high_tone.c
avr-objcopy -O ihex -R .eeprom high_tone.out high_tone.hex

avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:high_tone.hex
# Transferring the code into MeggyJr