/*
 * BuforCykliczny.c
 *
 * Created: 12.10.2017 19:37:09
 * Author : manie
 */ 
#define int8 uint8_t
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//port setup
	DDRC = 0b00000010;
	//PC0 - input - button
	//PC1 - output -LED
	
	//bufor setup
	int8 bufor[100];
	memset(bufor, 0, sizeof(int8)*100);
   	int8 index = 0;
	
    while (1) 
    {
		PORTC = 0b00000000;
		if (index == 100){
			index = 0;
		}
		if (bufor[index]){
			PORTC = 0b00000010;
			bufor[index] = 0;
		}
		if (PINC == 0b00000000){
			bufor[index] = 1;
		}
		index++;
		_delay_ms(10);
		
    }
}

