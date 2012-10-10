// This is the application which will make use of the library
// Claude Zhang
// John Weng
// Victor Wibisono
// modified from code by Eric McCreath, 2012

#include "library.h"

main() {
	meggy_init();
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