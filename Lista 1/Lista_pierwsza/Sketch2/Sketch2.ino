// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "b"
int main(void) {
	char serialCharacter;
	// -------- Inits --------- //
	LED_DDR = 0xff; /* set up LEDs for output */
	initUSART();
	printString("Hello World!\r\n"); /* to test */
	// ------ Event loop ------ //
	while (1) {
		serialCharacter = receiveByte();
		transmitByte(serialCharacter);
		LED_PORT = serialCharacter;
		/* display ascii/numeric value of character */
		} /* End event loop */
		return (0);
	}