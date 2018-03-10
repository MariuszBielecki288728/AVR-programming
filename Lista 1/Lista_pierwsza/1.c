
#define int8 uint8_t
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC  = 0b111111;
	PORTC = 0b100000;
	int8 left_to_right = 0;
	/* Replace with your application code */
	while (1)
	{
		if (PORTC == 0b00000001 || PORTC == 0b00100000){
			left_to_right = ~left_to_right;
		}
		_delay_ms(50);
		if (left_to_right){
			PORTC = PORTC >> 1;
		}
		else{
			PORTC = PORTC << 1;
		}
	}
}
