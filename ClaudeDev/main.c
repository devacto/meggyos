// Testing code for the Button Library for Meggy Jr
// Bowei Zhang, 2012

#include <avr/io.h>
#include "buttonlib.h"
#include "tonelib.h"

main() {
    initializeButtons( );

    while (1) {
        SPDR = getButtons( );
        while (!(SPSR & (1<<SPIF)));
        // Try to test if macros like BUTTONB works. Seems to be some problems
        // here...
        if (SPDR == BUTTONB) {
            PlayTone(ToneC3, 2000);
            delay(1000);
        }

        delay(1);
    }
}
