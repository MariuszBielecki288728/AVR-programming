/*
 * GrayLed.c
 *
 * Created: 12.10.2017 22:45:24
 * Author : manie
 */ 
#define RESET 0b00000001
#define PREV  0b00000010
#define NEXT  0b00000100

#define int8 uint8_t
#include <avr/io.h>
#include <util/delay.h>


void display(int8 num){
	PORTC = num;
}

int main(void)
{
	//setup
	DDRC = 0b00001111; // 4 * LED 
	
	int8 num = 0;
	display(0);
    int8 flag_button = 0; // 0 - default, 1 - NEXT, 2 - PREV, 3 - RESET
	while (1) 
    {
		if (PINC){
			_delay_ms(20);
			
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
		if (PINB == 0){
			switch(flag_button){
				case 1:
					if (num == 15){
						num = 0;
					}
					else{
						num++;
					}					
					display(num ^ (num >> 1));					
					break;
				case 2:
					if (num == 0){
						num = 15;
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

