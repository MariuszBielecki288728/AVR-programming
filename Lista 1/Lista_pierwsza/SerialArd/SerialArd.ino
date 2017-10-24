#include <avr/io.h>
#include <util/delay.h>
/*
void pwm_init()
{
	// initialize TCCR0 as per requirement, say as follows
	TCCR0A |= (1<<WGM00)|(1<<COM0A1)|(1<<WGM01)|(1<<CS00);
	
	// make sure to make OC0 pin (pin PB3 for atmega32) as output pin
	DDRB |= (1<<PORTB3);
}*/
void buzzi(unsigned long t){
	unsigned long i = 0;
	while (i<t){
		PORTB = 0b00001000;
		_delay_ms(1);
		PORTB = 0;
		_delay_ms(1);
		i = i + 2;
	}
	}

void display_char(char* chr){
	unsigned int kropka = 100;

	for (uint8_t i = 0; chr[i]; i++){
		switch (chr[i]){
			case '.':
			PORTC = 0b00111111;
			buzzi(kropka);			
			//_delay_ms(kropka);
			break;

			case '-':
			PORTC = 0b00111111;
			buzzi(kropka*3);
			//_delay_ms(kropka*3);
			break;
			
		}
		PORTC = 0;
		PORTD = 0;
		_delay_ms(kropka);
	}
	_delay_ms(kropka*3);
		
}

int main(void)
{
	DDRC = 0b00111111;
	DDRD = 0b10000100;
	DDRB = 0b00001000;
	init();
	uint8_t ch;
	Serial.begin(9600);
	
	char* chars[] = {".-","-...","-.-.","-..", ".", "..-.", "--.",
		"....", "..", ".---", "-.-", ".-..", "--",
		"-.", "---", ".--.", "--.-", ".-.", "...", "-",
		"..-", "...-", ".--", "-..-", "-.--", "--.."
	};
	char* num[] = {"------",".--.","..-..","...-.","....-","---","......","--..","-....","-..-"};
	

	
	while (1)
	{
		if (Serial.available()){
			
			ch = Serial.read();
			if (ch>='0' && ch<='9'){
				
				display_char(num[ch - '0']);
			} else if (ch>= 'A' && ch <= 'Z'){
				display_char(chars[ch-'A']);
			} else if (ch>= 'a' && ch <= 'z'){
				display_char(chars[ch-'a']);
				}
			if (ch == ' '){
				_delay_ms(400);
				
			}
		
		}
	}
}
