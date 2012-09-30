#!/bin/bash 

avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o lights.out lights.c
avr-objcopy -O ihex -R .eeprom lights.out lights.hex
avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:lights.hex
