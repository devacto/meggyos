// This is the application which will make use of the library
// Claude Zhang
// John Weng
// Victor Wibisono
// modified from code by Eric McCreath, 2012

#include "library.h"

main() {
	uart_init();
	uart_putchar('h'); // Serial out stuff

   while (1) {
       checkButtonsPress( );
       if (Button_B) {
            PlayTone(ToneC3, 10);
       }
   }
}