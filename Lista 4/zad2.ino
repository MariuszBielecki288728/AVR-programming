#define F_CPU 16000000UL
#define int8 uint8_t
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define LED PORTB0
#define LED_PORT PORTB
#define LED_DDR DDRB
#define BUTTON PIND7
#define BUTTON_PIN PIND





void initTimer(void) {
	
	//timer1
	TCCR1B |= (1 << WGM12); // TC1 CTC  top at	OCR1A
	TCCR1B |= (1 << CS11) ; //cpu/8
	// initialize counter
	TCNT1 = 0;
	// initialize compare value (10ms)
	OCR1A = 19999;
	// enable compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	// enable global interrupts
	sei();
	
}

volatile int8 bufor[100];
volatile int8 index;

ISR (TIMER1_COMPA_vect)
{
	LED_PORT = 0;
	if (index == 99){
		index = 0;
	}
	if (bufor[index]){
		LED_PORT |= (1 << LED);
		bufor[index] = 0;
	}
	if (BUTTON_PIN & (1 << BUTTON)){
		bufor[index] = 1;
	}
	index++;
}


int main(void)
{
	//bufor setup
	memset(bufor, 0, sizeof(int8)*100);
	index = 0;
	//sleep mode select - IDLE
	set_sleep_mode(SLEEP_MODE_IDLE);
	//port setup
	LED_DDR = (1 << LED);

	initTimer();
	while (1)
	{
		sleep_mode();
	}
}
