#!/bin/bash
if [ $# != 1 ]
then
    echo "Usage: compile.sh tone (not tone.c!)"
else
    avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o $1.out $1.c
    avr-objcopy -O ihex -R .eeprom $1.out $1.hex
    avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:$1.hex
fi
