#include<avr/interrupt.h>
#include "our_screen.h"


extern uint8_t fbRed[];
extern uint8_t fbGreen[];
extern uint8_t fbBlue[];
extern uint8_t fbLights;

uint16_t i=0;

main()
{
    

    turnOnFrameBuffer();
    fbLights = 0xAAU;
    fbRed[0] = 0x08U;
    fbGreen[1] = 0xFFU;
    fbBlue[2] = 0x11U;
    fbRed[3] = 0x80U;
    fbRed[4] = 0x40U;
    fbRed[5] = 0x20U;
    fbRed[6] = 0x10U;
    fbRed[7] = 0xAAU;
    
    DDRB |= 1<<PB1;   // set pin 15 to output
   
   TCCR2A = (1<<WGM21); // clear timer on compare match
   TCCR2B = (1<<CS21);  // timer uses main system clock with 1/8 prescale
   OCR2A  = (F_CPU >> 3) / 8 / 15 / 120; 
   TIMSK2 = (1<<OCIE2A); // call interrupt on output compare match

   sei( );    // Enable interrupts

    while(1)
    {
        drawFrameBuffer();
        
    }
}


ISR(TIMER2_COMPA_vect)
{
    i++;
    if (i>2000)
    {
        fbLights =  (fbLights << 1) | (fbLights >> 7);
        for (i =0; i < 8 ; i++)
        {    
            fbRed[i] = (fbRed[i] << 1) | (fbRed[i] >> 7);
        }
    }
    
}

