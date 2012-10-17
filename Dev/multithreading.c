// This is the application which will make use of the library
// Claude Zhang
// John Weng
// Victor Wibisono
// modified from code by Eric McCreath, 2012

#include "library.h"

uint16_t k = 48;
uint16_t j = 48;
uint16_t i = 0;

uint16_t sp[2] = {0x0000,0x0000};


/*
 *
 * The #i bit of his variable is used as: 
 * #0. a flag used to direct scheduling
 * #1. a flag indicating synchronize query
 * #2. a semaphore for thread 1
 * #3. a semaphore for thread 2
 */
#define MTscheduling    0
#define MTsynchronize   1
#define MTsemaphore_1   2
#define MTsemaphore_2   3

uint8_t schedulingFlag = 0;


main() {
    meggyInit();
    // Serial out stuff
    sei();
    while (1) {

        drawFrameBuffer();

        checkButtonsDown( );

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

    }
}



// Interrupt Service Routine (ISR) stuff

// ISR for timer 0
ISR(TIMER0_COMPA_vect, ISR_NAKED)
{
    asm("push r0");
    asm("push r1");
    asm("push r2");
    asm("push r3");
    asm("push r4");
    asm("push r5");
    asm("push r6");
    asm("push r7");
    asm("push r8");
    asm("push r9");
    asm("push r10");
    asm("push r11");
    asm("push r12");
    asm("push r13");
    asm("push r14");
    asm("push r15");
    asm("push r16");
    asm("push r17");
    asm("push r18");
    asm("push r19");
    asm("push r20");
    asm("push r21");
    asm("push r22");
    asm("push r23");
    asm("push r24");
    asm("push r25");
    asm("push r26");
    asm("push r27");
    asm("push r28");
    asm("push r29");
    asm("push r30");
    asm("push r31");


    /*
     * Create initial two threads
     */

    if(!sp[0] && !sp[1])
    {
         asm("pop r31");
    asm("pop r30");
    asm("pop r29");
    asm("pop r28");
    asm("pop r27");
    asm("pop r26");
    asm("pop r25");
    asm("pop r24");
    asm("pop r23");
    asm("pop r22");
    asm("pop r21");
    asm("pop r20");
    asm("pop r19");
    asm("pop r18");
    asm("pop r17");
    asm("pop r16");
    asm("pop r15");
    asm("pop r14");
    asm("pop r13");
    asm("pop r12");
    asm("pop r11");
    asm("pop r10");
    asm("pop r9");
    asm("pop r8");
    asm("pop r7");
    asm("pop r6");
    asm("pop r5");
    asm("pop r4");
    asm("pop r3");
    asm("pop r2");
    asm("pop r1");
    asm("pop r0");
        
        asm("push r0");
        asm("push r1");
        asm("push r2");
        asm("push r3");
        asm("push r4");
        asm("push r5");
        asm("push r6");
        asm("push r7");
        asm("push r8");
        asm("push r9");
        asm("push r10");
        asm("push r11");
        asm("push r12");
        asm("push r13");
        asm("push r14");
        asm("push r15");
        asm("push r16");
        asm("push r17");
        asm("push r18");
        asm("push r19");
        asm("push r20");
        asm("push r21");
        asm("push r22");
        asm("push r23");
        asm("push r24");
        asm("push r25");
        asm("push r26");
        asm("push r27");
        asm("push r28");
        asm("push r29");
        asm("push r30");
        asm("push r31");


        asm("push r0");

        asm("push r0");
        asm("push r1");
        asm("push r2");
        asm("push r3");
        asm("push r4");
        asm("push r5");
        asm("push r6");
        asm("push r7");
        asm("push r8");
        asm("push r9");
        asm("push r10");
        asm("push r11");
        asm("push r12");
        asm("push r13");
        asm("push r14");
        asm("push r15");
        asm("push r16");
        asm("push r17");
        asm("push r18");
        asm("push r19");
        asm("push r20");
        asm("push r21");
        asm("push r22");
        asm("push r23");
        asm("push r24");
        asm("push r25");
        asm("push r26");
        asm("push r27");
        asm("push r28");
        asm("push r29");
        asm("push r30");
        asm("push r31");

        sp[1] = SP;
        sp[0] = SP - 0x21;
        SP = SP - 0x41;
        asm("pop r0");
        SP = SP + 0x21;
        asm("push r0");
        SP = sp[1];

    }

    /*
     * Scheduling
     */

    if( schedulingFlag & (1 << MTsynchronize) )
    {   
        SP = sp[0] - 0x20;
        asm("pop r0");
        SP = sp[1] - 0x20;
        asm("pop r1");
        asm("cp r0, r1");
        asm("brlo .L13");
        //if(r0<r1)
            SP = sp[0];
        //else
        asm(".L13:");
            SP = sp[1];
    }
    else if( schedulingFlag & (1<< MTsemaphore_1) )
    {
        SP = sp[0];
    }
    else if( schedulingFlag & (1<<MTsemaphore_2) )
    {
        SP = sp[1];
    }
    /*
     * 
     * Following two condition is used for RR Scheduling
     *
     */
    else if( schedulingFlag & (1<<MTscheduling) )
    {
        SP = sp[0];
        schedulingFlag &= ~(1<<MTscheduling);
    }
    else if( !(schedulingFlag & (1<<MTscheduling)))
    {
        SP = sp[1];
        schedulingFlag |= 1<<MTscheduling;
    }


    asm("pop r31");
    asm("pop r30");
    asm("pop r29");
    asm("pop r28");
    asm("pop r27");
    asm("pop r26");
    asm("pop r25");
    asm("pop r24");
    asm("pop r23");
    asm("pop r22");
    asm("pop r21");
    asm("pop r20");
    asm("pop r19");
    asm("pop r18");
    asm("pop r17");
    asm("pop r16");
    asm("pop r15");
    asm("pop r14");
    asm("pop r13");
    asm("pop r12");
    asm("pop r11");
    asm("pop r10");
    asm("pop r9");
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
