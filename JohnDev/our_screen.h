/*
 *
 *
 *
 */

#include <avr/io.h>

uint8_t fbRed[8];
uint8_t fbGreen[8];
uint8_t fbBlue[8];
uint8_t fbLights;

void delay(uint16_t ms);

void turnOnFrameBuffer();

void drawFrameBuffer(uint8_t ledRow, uint8_t lightsFlag);

void drawFrameBufferOld();
