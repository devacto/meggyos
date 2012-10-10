// This is the application which will make use of the library
// Claude Zhang
// John Weng
// Victor Wibisono
// modified from code by Eric McCreath, 2012

#include "library.h"

main() {
	meggyInit();
	 // Serial out stuff
   while (1) {
       checkButtonsDown( );
       if (Button_B) {
			playTone(ToneC3, 50);
			uart_putchar('b');
       } 

		if (Button_A) {
			playTone(ToneD3, 50);
			uart_putchar('a');
		 } 
		
		if (Button_Up) {
			playTone(ToneE3, 50);
			uart_putchar('u');
		 }
		
		if (Button_Down) {
			playTone(ToneF3, 50);
			uart_putchar('d');
		}
		
		if (Button_Left) {
			playTone(ToneG3, 50);
			uart_putchar('l');
		} 
		
		if (Button_Right) {
			playTone(ToneA3, 50);
			uart_putchar('r');
		}
   }
}

// Interrupt Service Routine (ISR) stuff

// ISR for timer 0
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