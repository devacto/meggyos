#include <avr/io.h>

#define BUTTONB     0x01U
#define BUTTONA     0x02U
#define BUTTONUP    0x04U
#define BUTTONDOWN  0x08U
#define BUTTONLEFT  0x10U
#define BUTTONRIGHT 0x20U

extern void initializeButtons( );
extern uint8_t getButtons( );
extern void delay(uint16_t ms);
