#include <avr/io.h>
#include "sample.h"
#include <pgmspace.h>
#define SPEAKER_DDR DDRD
#define SPEAKER 6
void initTimer(void) {
	
	//timer1
	TCCR1B |= (1 << WGM12); // TC1 CTC  top at	OCR1A
	TCCR1B |= (1 << CS10) ; //cpu/1
	// initialize counter
	TCNT1 = 0;
	// initialize compare value
	OCR1A = 999;
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
	// change sample here
	OCR0A = pgm_read_byte(&(sample[i]));
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
