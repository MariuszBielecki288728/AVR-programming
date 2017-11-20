#include <avr/io.h>
#include <util/delay.h>
#define LED_DDR DDRB
#define LED PORTB3
#define LED_BR OCR2A

static inline void initADC0(void) {
	ADMUX |= (1 << REFS0); /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);// | (1 << ADPS0); /* ADC clock prescaler /8 */
	ADCSRA |= (1 << ADEN); /* enable ADC */
}
static inline void initTimer(void) {
	//timer2 PORTB3
	TCCR2A |= (1 << COM2A1); //non inverting
	TCCR2A |= (1 << WGM20)  | (1 << WGM21);  //fast pwm 8bit
	TCCR2B |= (1 << CS20); /* CPU clock / 1 => 31250Hz */
}

int main(void)
{
	uint16_t adc_value;
	initTimer();
	initADC0();
	LED_DDR |= (1 << LED);
	float u;
	uint32_t imp;
	/* Replace with your application code */
	while (1)
	{
		ADCSRA |= (1 << ADSC); /* start ADC conversion */
		while (ADCSRA & (1 << ADSC));
		adc_value = ADC;
		u = 5 - (adc_value * 5.0) / 1023.0; //u = 5.0 - (adc_value * 5.0) / 1023.0;
		imp = (u * 47000) / (5 - u + 5); //imp = (u * 47000) / (5 - u + 0.55);
		LED_BR = ((imp / 50000.0)*255) ;
		_delay_ms(50);
		
	}
}

