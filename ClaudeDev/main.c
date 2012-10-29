// This is the application which will make use of the library
// Bowei Zhang
// Zhe Weng
// Victor Wibisono
// modified from code by Eric McCreath, 2012

#include "meggyLibrary.h"
#include "gameLibrary.h"

#define MULTI_THREAD_NUMBER 2
#define MULTI_SP_LENGTH 34
#define MULTI_SWITCH_RATE 250

/*
 * This var is used to store the Stack Pointer where 
 * storing the 32 registers data and return address 
 * of thread i
 */
uint16_t multiSP[MULTI_THREAD_NUMBER][MULTI_SP_LENGTH];


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

uint8_t schedulingFlag = 0x01;
uint8_t runningThread = 0;
uint8_t globalTemp;
uint8_t globalCounter = 0;

Snake     snake;
Fruit     fruit;
Gamestage gameStage = Welcome;

void loop(uint16_t* cnt)
{
    if (gameStage == Welcome) {

        displayWelcomePage(&gameStage, &snake, &fruit);

    } else if (gameStage == Ongoing) {
    
        // when the game is on, buzzer will make a sound at the same time
        if (runningThread == 0) {
            checkButtonsPress( );
        } 
        /*
        if (runningThread == 1) {
            playTone(ToneB2, 40);
        }
        */
         
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
        eatFruit(&snake, &fruit);

    } else {

        displayGameOverPage(&gameStage);
    }
    
    // reset counter
    *cnt = 0;
}

void drawGame( )
{
    cleanFrameBuffer( );
    drawSnake(snake);
    drawFruit(fruit);
    drawFrameBuffer( );
}

void getAddr(unsigned char num)
{
    for (globalTemp = 1; globalTemp <= MULTI_SP_LENGTH; globalTemp++) {
        multiSP[num][globalTemp - 1] = (*((unsigned char *)(SP + globalTemp)));
    }
}

void putAddr()
{
    /*
    if (runningThread == 0 && globalCounter <= MULTI_SWITCH_RATE) {
        globalCounter++;
        return ;
    }
    */
    if (runningThread == 0) {
        for (globalTemp = 0; globalTemp < MULTI_SP_LENGTH; globalTemp++) {
            multiSP[0][globalTemp] = (*((unsigned char *)(SP + globalTemp)));
        }

        if (++globalCounter > MULTI_SWITCH_RATE) {
            for(globalTemp=0; globalTemp < MULTI_SP_LENGTH; globalTemp++) {
                (*(unsigned char *)(SP + globalTemp)) = multiSP[1][globalTemp];
            }
            runningThread = 1;
        }
    } else {
        for (globalTemp = 0; globalTemp < MULTI_SP_LENGTH; globalTemp++) {
            multiSP[1][globalTemp] = (*((unsigned char *)(SP + globalTemp)));
            (*(unsigned char *)(SP + globalTemp)) = multiSP[0][globalTemp];
        }
        globalCounter = 0;
        runningThread = 0;
    }
}

main() {
    // this counter is used to control the rate of refreshing
    uint16_t cnt = 0;
    // this frame counter is used to decide which 'ring' of splash screen
    // to show
    uint16_t frame = 0;
    uint16_t sound = 0;

    meggyInit();
    
    if (schedulingFlag & (1 << MTscheduling)) {
        runningThread = 0;
        getAddr(0);
        getAddr(1);
    }

    // this while loop is used to display the welcome splash screen
    
    while (1) {
        if (cnt % 32 == 0) {
            ++frame;
        }
        // the screen only lasts until cnt reaches 3000
        if (cnt > 2500) {
            break;
        } else {
            ++cnt;
        }
        if (runningThread == 1) {
            welcomeRingTone(sound++);
        } else {
            showSplashScreen(frame);
        }
        putAddr();
    }
    
    cnt = 0;

    if (schedulingFlag & (1 << MTscheduling)) {
        runningThread = 0;
        getAddr(0);
        getAddr(1);
    }

    // this loop is the main loop of the game
    while (1) {
        // snake.length * 10 is used to offset the overhead brought by
        // calculations of the snake body. Since the bigger the body is, the
        // longer time it takes to compute
        cnt > 301 - snake.length * 10 ? loop(&cnt) : cnt++;
        if (gameStage == Ongoing) {
            // draw snake and fruit on the slate
            drawGame( );
            checkCollision(&gameStage, &snake, &fruit);
        }
        if (runningThread == 1) {
            playTone(ToneB2, 2);
        }
        putAddr();
    }
}

SIGNAL(TIMER2_COMPA_vect)
{
    // thread 0
    if (runningThread == 0) {
        for (globalTemp = 0; globalTemp < MULTI_SP_LENGTH; globalTemp++) {
            multiSP[0][globalTemp] = (*(unsigned char*)(SP + globalTemp));
            (*(unsigned char*)(SP + globalTemp)) = multiSP[1][globalTemp];
        } 
        runningThread = 1;
    } else {
        for (globalTemp = 0; globalTemp < MULTI_SP_LENGTH; globalTemp++) {
            multiSP[1][globalTemp] = (*(unsigned char*)(SP + globalTemp));
            (*(unsigned char*)(SP + globalTemp)) = multiSP[0][globalTemp];
        } 
        runningThread = 0;
    }
}
