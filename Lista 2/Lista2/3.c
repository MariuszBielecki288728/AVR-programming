#include <avr/io.h>
#include "sounddata.h"
#include <avr/pgmspace.h>
#define SPEAKER_DDR DDRD
#define SPEAKER 6
void initTimer(void) {
	
	//timer1
	TCCR1B |= (1 << WGM12); // TC1 CTC  top at	OCR1A
	TCCR1B |= (1 << CS10) ; //cpu/1
	// initialize counter
	TCNT1 = 0;
	// initialize compare value
	OCR1A = 1500;
	// enable compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	// enable global interrupts
	sei();
	
	
	//timer2B OC2B PD3
	TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TCCR0B |= (1 << CS00);
}
uint32_t index = 0;
ISR (TIMER1_COMPA_vect)
{
	uint8_t smpl;
	if (!(smpl = pgm_read_byte(&(sounddata_data[index])))){
		index = 0;
	}
	// change sample here
	OCR0A = smpl;
	index++;	
}


int main(void)
{
	
	initTimer();
	SPEAKER_DDR |= (1 << SPEAKER);
	while (1)
	{
		
	}
}
