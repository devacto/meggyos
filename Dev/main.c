// This is the application which will make use of the library
// Claude Zhang
// John Weng
// Victor Wibisono
// modified from code by Eric McCreath, 2012

#include "library.h"

uint16_t k = 48;
uint16_t j = 48;
uint16_t i = 0;

main() {
	meggyInit();
	 // Serial out stuff
	sei();
   while (1) {
		// the main function should do nothing
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
    
	drawFrameBuffer();
    
	k++;
    if (k > 2000) {
		uart_putchar('0');
		k = 0;
        fbGreen[1] = (fbGreen[1] << 1) | (fbGreen[1] >> 7);
    }

	sei();
	
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
	

	if (Button_B) {
			playTone(ToneC3, 50);
			uart_putchar('b');
			drawPixel(0,0,redIndex);
       } 

		if (Button_A) {
			playTone(ToneD3, 50);
			uart_putchar('a');
			drawPixel(1,1,greenIndex);
		 } 
		
		if (Button_Up) {
			playTone(ToneE3, 50);
			uart_putchar('u');
			drawPixel(2,2,blueIndex);
		 }
		
		if (Button_Down) {
			playTone(ToneF3, 50);
			uart_putchar('d');
			drawPixel(3,3,iceIndex);
		}
		
		if (Button_Left) {
			playTone(ToneG3, 50);
			uart_putchar('l');
			drawPixel(4,4,magentaIndex);
		} 
		
		if (Button_Right) {
			playTone(ToneA3, 50);
			uart_putchar('r');
			drawPixel(5,5,yellowIndex);
		}
    
    j++;
    if (j > 2000) {
		uart_putchar(j);
		j = 48;
        //fbGreen[1] = (fbGreen[1] << 1) | (fbGreen[1] >> 7);
    }

	sei();
	
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
	
	checkButtonsDown( );
    
    i++;
    if (i>2000)
    {
        fbLights =  (fbLights << 1) | (fbLights >> 7);
        for (i =0; i < 8 ; i++)
        {    
            fbRed[i] = (fbRed[i] << 1) | (fbRed[i] >> 7);
        }
    }

	sei();
	
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
