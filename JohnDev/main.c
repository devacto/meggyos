#include<avr/interrupt.h>
#include "our_screen.h"


extern uint8_t fbRed[];
extern uint8_t fbGreen[];
extern uint8_t fbBlue[];
extern uint8_t fbLights;

uint16_t i=0,j=0,k=0;


main()
{
    turnOnFrameBuffer();
    fbLights = 0xAAU;
    fbRed[0] = 0x08U;
    fbGreen[1] = 0xCCU;
    fbRed[1] = 0xF0U;
    fbBlue[1] = 0xAAU;
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

    TCCR1A = (1<<WGM21); // clear timer on compare match
    TCCR1B = (1<<CS21);  // timer uses main system clock with 1/8 prescale
    OCR1A  = (F_CPU >> 3) / 8 / 15 / 120; 
    TIMSK1 = (1<<OCIE1A); // call interrupt on output compare match
    
    
    TCCR0A = (1<<WGM21); // clear timer on compare match
    TCCR0B = (1<<CS21);  // timer uses main system clock with 1/8 prescale
    OCR0A  = (F_CPU >> 3) / 8 / 15 / 120; 
    TIMSK0 = (1<<OCIE0A); // call interrupt on output compare match
    
    //sei( );    // Enable interrupts

    while(1)
    {
        drawFrameBuffer();
        
    }
}


ISR(TIMER0_COMPA_vect, ISR_NAKED)
{
    static uint16_t sph, spl;
    asm("push r0");
    asm("push r1");
    asm("push r2");
    asm("push r3");
    asm("push r4");
    asm("push r5");
    asm("push r6");
    asm("push r7");
    asm("push r8");
    sph = SPH;
    spl = SPL;
    
    sei();
    k++;
    if(k>100)
        fbGreen[1] = (fbGreen[1] << 1) | (fbGreen[1] >> 7);
    
    SPH = sph;
    SPL = spl;
    asm("pop r8");
    asm("pop r7");
    asm("pop r6");
    asm("pop r5");
    asm("pop r4");
    asm("pop r3");
    asm("pop r2");
    asm("pop r1");
    asm("pop r0");
    reti();
}



ISR(TIMER1_COMPA_vect, ISR_NAKED)
{
    static uint16_t sph, spl;
    asm("push r0");
    asm("push r1");
    asm("push r2");
    asm("push r3");
    asm("push r4");
    asm("push r5");
    asm("push r6");
    asm("push r7");
    asm("push r8");
    sph = SPH;
    spl = SPL;

    sei();
    j++;
    if(j>100)
        fbBlue[2] = (fbBlue[2] << 1) | (fbBlue[2] >> 7);
    
    SPH = sph;
    SPL = spl;
    asm("pop r8");
    asm("pop r7");
    asm("pop r6");
    asm("pop r5");
    asm("pop r4");
    asm("pop r3");
    asm("pop r2");
    asm("pop r1");
    asm("pop r0");
    reti();
}


ISR(TIMER2_COMPA_vect, ISR_NAKED)
{
    static uint16_t sph, spl;
    asm("push r0");
    asm("push r1");
    asm("push r2");
    asm("push r3");
    asm("push r4");
    asm("push r5");
    asm("push r6");
    asm("push r7");
    asm("push r8");
    sph = SPH;
    spl = SPL;

    sei();
    i++;
    if (i>2000)
    {
        fbLights =  (fbLights << 1) | (fbLights >> 7);
        for (i =0; i < 8 ; i++)
        {    
            fbRed[i] = (fbRed[i] << 1) | (fbRed[i] >> 7);
        }
    }

    SPH = sph;
    SPL = spl;
    asm("pop r8");
    asm("pop r7");
    asm("pop r6");
    asm("pop r5");
    asm("pop r4");
    asm("pop r3");
    asm("pop r2");
    asm("pop r1");
    asm("pop r0");

    reti();
}



