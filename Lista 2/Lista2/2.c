#include <avr/io.h>
#include <util/delay.h>
#define IR_LED PORTD3
#define IR_IN PINC0
#define IR_IN_DDR DDRC
#define IR_LED_DDR DDRD
#define LED PORTB3
#define LED_DDR DDRB
#define IR_FREQ 210 //compare, CTC, 8 bit, cpu/1, 37.9khz
void setup(void){

	
}
void initTimer(void) {
	
	//timer1
	TCCR1B |= (1 << WGM12); // TC1 CTC  top at	OCR1A
	TCCR1B |= (1 << CS10) | (1 << CS12); //cpu/1024
	// initialize counter
	TCNT1 = 0;	
	// initialize compare value
	OCR1A = 350;	
	// enable compare interrupt
	TIMSK1 |= (1 << OCIE1A);	
	// enable global interrupts
	sei();
	
	
	//timer2B OC2B PD3
	TCCR2A |= (1 << COM2B0) | (1 << WGM21);
	TCCR2B |= (1 << CS20);
} 
ISR (TIMER1_COMPA_vect)
{
	// toggle led here 
	IR_LED_DDR ^= (1 << IR_LED);
}
int main(void)
{	

	initTimer();
	OCR2B = IR_FREQ;
	LED_DDR |= (1 << LED);
	IR_LED_DDR |= (1 << IR_LED);
	PORTC |= (1 << IR_LED); //pullup
  
	while (1){
		if (!(PINC & (1 << IR_IN))){
			PORTB |= (1 << LED);
		}else
		PORTB &= ~(1<<LED);
		}
}