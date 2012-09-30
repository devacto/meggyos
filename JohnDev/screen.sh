#!/bin/bash 

avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o screen.out screen.c
avr-objcopy -O ihex -R .eeprom screen.out screen.hex
avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:screen.hex
