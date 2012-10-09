// This is the application which will make use of the library
// Claude Zhang
// John Weng
// Victor Wibisono
// modified from code by Eric McCreath, 2012

#include "library.h"

main() {
    /*
	PlayTone(ToneC3, 1000); // 1000 is 2 seconds
	PlayTone(ToneD3, 1000);
	PlayTone(ToneE3, 1000);
	PlayTone(ToneF3, 1000);
	PlayTone(ToneG3, 1000);
    */

    while (1) {
        checkButtonsPress( );
        if (Button_B) {
            PlayTone(ToneC3, 10);
        }
    }
}
