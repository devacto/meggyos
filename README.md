meggyos
=======

Operating System / Library for Meggy Jr Boards.

Due Date
========

October 29, 2012

We aim to finish development by October 23, 2012. From then on we will concentrate on writing the report and preparing the in-class demonstration.

Meggy Jr is not recognized by Mac OS X?
==================================

According to [this page](http://www2.evilmadscientist.com/forum/viewtopic.php?showtopic=4890),
first check the cable connection. If it still doesn't work, download FTDI VCP
from [here](http://www.ftdichip.com/Drivers/VCP.htm)


AVR working suit on Mac OS X
==================================
* AVR-GCC compilor
    sudo port install avr-gcc
* AVC C library
    sudo port install avr-libc
* AVR DUDE ?
    sudo port install avrdude

Compiling
=========
Use the script under / to compile the project. Say if you want get tone.c
compiled and upload it to the Meggy. Use the command below(_Make sure Meggy is
        on_):
<pre>sh compile.sh tone</pre>
Then you could enjoy her screaming:)

AVRDUDE for Mac OS X
====================

Instead of the usual tty.usb0, we have to use tty.usbserial-A501JU54.

For example, in order to transfer main.hex into the Meggy board, we can use:
<pre>avrdude -b57600 -patmega328p -cstk500v1 -P/dev/tty.usbserial-A501JU54 -U flash:w:main.hex</pre>
