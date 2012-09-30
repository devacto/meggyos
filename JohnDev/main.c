#include "our_screen.h"


extern uint8_t fbRed[];
extern uint8_t fbGreen[];
extern uint8_t fbBlue[];
extern uint8_t fbLights;

int main()
{
    int i;

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

    while(1)
    {
        drawFrameBuffer();
        i++;
        if (i >= 1000)
        {        
            fbLights =  (fbLights << 1) | (fbLights >> 7);
            for (i =0; i < 8 ; i++)
                fbRed[i] = (fbRed[i] << 1) | (fbRed[i] >> 7);
        }
    }
}
