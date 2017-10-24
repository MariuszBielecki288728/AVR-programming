#define RESET 0b00000001
#define PREV  0b00000010
#define NEXT  0b00000100

#define BUTTONS (PINB & 0b0000111)
#define CONTROL_LED(x) (PORTD = x << PORTD7)
#define int8 uint8_t
#include <avr/io.h>
#include <util/delay.h>


void display(int8 num){
	PORTC = num;
}

int main(void)
{
	//setup
	DDRC = 0b00111111; // 6 * LED 
	DDRD = 1 << DDD7;
	int8 num = 0;
	
    int8 flag_button = 0; // 0 - default, 1 - NEXT, 2 - PREV, 3 - RESET
	while (1) 
    {
		if (BUTTONS){// PINB05 siê swieci z jakeigos powodu
			CONTROL_LED(1);
			_delay_ms(20);
			CONTROL_LED(0);
			//NEXT
			if(PINB & NEXT) {
				flag_button = 1;
			}
			//PREV
			else if(PINB & PREV) {
				flag_button = 2;
			}
			//RESET
			else if(PINB & RESET) {
				flag_button = 3;
			}
		}
		if (flag_button){
			//display(PINB);
			if (!(BUTTONS)){
			
				switch(flag_button){
					case 1:
						if (num == 63){
							num = 0;
						}
						else{
							num++;
						}					
						display(num ^ (num >> 1));					
						break;
					case 2:
						if (num == 0){
							num = 63;
						}
						else{
							num--;
						}					
						display(num ^ (num >> 1));					
						break;
					case 3:
						num = 0;
						display(0);
						break;
				}
			flag_button = 0;
			}
		}
	}
}

