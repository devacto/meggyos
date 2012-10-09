// Testing code for the Button Library for Meggy Jr
// Bowei Zhang, 2012

#include <avr/io.h>
#include "buttonlib.h"
#include "tonelib.h"

main() {
    
    TCCR0A = (1<<WGM21); // clear timer on compare match
    TCCR0B = (1<<CS21);  // timer uses main system clock with 1/8 prescale
    OCR0A  = 100;//(F_CPU >> 3) / 8 / 15 / 120; 
    TIMSK0 = (1<<OCIE0A); // call interrupt on output compare match
    

    initializeButtons( );
    sei( );

    while (1) {
        SPDR = getButtons( );
        while (!(SPSR & (1<<SPIF)));
        // Try to test if macros like BUTTONB works. Seems to be some problems
        // here...
        delay(0);
    }
}


ISR(TIMER0_COMPA_vect)
{
    sei( );
    if (SPDR & BUTTONB) {
        PlayTone(ToneA3, 100);
    //    PlayTone(ToneB3, 200);
     //   PlayTone(ToneC3, 200);
      //  PlayTone(ToneD3, 200);
       // PlayTone(ToneE3, 200);
        delay(0);
    }
}
