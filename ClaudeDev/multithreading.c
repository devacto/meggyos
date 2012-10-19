// This is the application which will make use of the library
// Claude Zhang
// John Weng
// Victor Wibisono
// modified from code by Eric McCreath, 2012

#include "meggyLibrary.h"
#include "gameLibrary.h"

uint16_t k = 48;
uint16_t j = 48;
uint16_t i = 0;


/*
 * This var is used to store the Stack Pointer where 
 * storing the 32 registers data and return address 
 * of thread i
 */
uint16_t sp[2] = {0x0000,0x0000};


/*
 * The #i bit of this variable is used as: 
 * #0. a flag used to direct scheduling
 * #1. a flag indicating synchronize query
 * #2. a semaphore for thread 1
 * #3. a semaphore for thread 2
 * #4. a flag indicating EDF
 */
#define MTscheduling    0
#define MTsynchronize   1
#define MTsemaphore_1   2
#define MTsemaphore_2   3
#define MTEDF           4

uint8_t schedulingFlag = 0;

Snake     snake;
Gamestage gameStage = Welcome;

void loop(uint16_t* cnt)
{
    if (gameStage == Welcome) {
        displayWelcomePage(&gameStage);
    } else if (gameStage == Ongoing) {
    
        checkButtonsPress( );
    
        if (Button_Up && snake.dir != Down) {
            snake.dir = 1;
        } else if (Button_Down && snake.dir != Up) {
            snake.dir = 2;
        } else if (Button_Left && snake.dir != Right) {
            snake.dir = 3;
        } else if (Button_Right && snake.dir != Left) {
            snake.dir = 4;
        } 
    
        updateSnakeLocation(&snake);
        // reset counter
    } else {
        displayGameOverPage( );
        gameStage = Welcome;
    }
    *cnt = 0;
}

void draw( )
{
    cleanFrameBuffer( );
    drawSnake(snake);
    drawFrameBuffer( );
}

main() {
    // this counter is used to control the rate of refreshing
    uint16_t cnt = 0;

    snake.length = 0;
    meggyInit();
    // Serial out stuff
//    sei();
    while (1) {
        cnt > 250 ? loop(&cnt) : cnt++;
        if (gameStage == Ongoing) {
            draw( );
        }
    }
}

// Interrupt Service Routine (ISR) stuff

// ISR for timer 0

ISR(TIMER0_COMPA_vect, ISR_NAKED)
{
    /*
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
*/

    /*
     * Create initial two threads
     * The stack configuration is :
     *  #-65 thread 1 return address
     *  #-64 R0 for thread 1
     *      ... ...
     *  #-33 R31 for thread 1           <- sp[0]
     *  #-32 thread 2 return address
     *  #-31 R0 for thread 2
     *      ... ...
     *  #0   R31 for thread 2           <- sp[1]
     */

 //   if(!sp[0] && !sp[1])
  //  {
        /*
         * To make two identical threads initially, we restore all
         * the registers again
         */
/*
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
 */       
        /*
         * Stack configuration for thread 1
         */
/*
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
*/
        /*
         * Thread configuration for thread 2
         */
/*
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
 */       
        /*
         * Fix the initial return address of thread 2
         */
    /*
        SP = SP - 0x41;
        asm("pop r0");
        SP = SP + 0x21;
        asm("push r0");
        */
//    }

    /*
     * Scheduling Part
     */

    /*
     * To synchronize two threads, we let the advanced thread 
     * wait slower one
     */
    /*
    if( schedulingFlag & (1 << MTsynchronize) )
    {   
        SP = sp[0] - 0x20;
        asm("pop r0");
        SP = sp[1] - 0x20;
        asm("pop r1");
        asm("cp r0, r1");
        asm("brlo .haha");
        //if(r0<r1)
        SP = sp[0];
        //else
        asm(".haha:");
        SP = sp[1];
    }*/
    /*
     * Following two condition are used for semaphore 
     * checking
     */
    /*
    else if( schedulingFlag & (1<< MTsemaphore_1) )
    {
        SP = sp[0];
    }
    else if( schedulingFlag & (1<<MTsemaphore_2) )
    {
        SP = sp[1];
    }*/
    /*
     * Following two condition are used for RR Scheduling
     */
    /*
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
    else if( schedulingFlag & (1 << MTEDF) ) 
    { */  
    /*
     * EDF Scheduling
     */
    /*
        SP = sp[0] - 0x20;
        asm("pop r0");
        SP = sp[1] - 0x20;
        asm("pop r1");
        asm("cp r0, r1");
        asm("brlo .hehe");
        //if(r0<r1)
        SP = sp[1];
        //else
        asm(".hehe:");
        SP = sp[0];
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
*/
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
    if (j > 200) {
        uart_putchar(j);
        j = 48;
        //fbGreen[1] = (fbGreen[1] << 1) | (fbGreen[1] >> 7);
    }

//    sei();
    

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

/*
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
*/

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
