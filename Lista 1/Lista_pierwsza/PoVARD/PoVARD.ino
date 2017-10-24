#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0b00111111;
	uint8_t col[] = {10,
		 0b00111000,
		 0b00001000, 
		 0b00001000,
		 0b00111111,
		 0b00000000, 
		 0b00000000, 
		 0b00101111, 
		 0b00101001,
		 0b00101001, 
		 0b00111001}; 
	uint8_t col1[] = {
		 0b00000000,
		 0b00000000,
		 0b00111111,
		 0b00000000,
		 0b00000000,
		 0b00111111,
		 0b00100001,
		 0b00100001,
		 0b00111111};
	/* Replace with your application code */
	while (1)
	{
		for (uint8_t i = 1; i<=col[0]; i++){
			PORTC = col[i];
			_delay_ms(13);
		}
		PORTC =0;
		//_delay_ms(10);
	}
}
