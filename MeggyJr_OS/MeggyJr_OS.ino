#include <MeggyJr.h>

uint8_t CT[14][3] = 
     {{MeggyDark},  
      {MeggyRed},
      {MeggyOrange},
      {MeggyYellow},
      {MeggyGreen},
      {MeggyBlue},
      {MeggyViolet},
      {MeggyWhite},
      {0,0,1},     
      {0,1,0},      
      {1,0,0},
      {1,1,0},
      {0,3,1},
      {2,0,1}};       
     
enum colors {Dark, Red, Orange, Yellow, Green, Blue, Violet, White, 
         dimBlue, dimGreen, dimRed, dimYellow, dimAqua, dimViolet };

uint8_t redMatrix[9];
uint8_t grnMatrix[9];
uint8_t bluMatrix[9];

