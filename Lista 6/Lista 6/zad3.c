
#include <avr/io.h>

void initADC0(void) {
	ADMUX  |= (1 << REFS0); // ref vol on AVCC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);// ADC clock /64
	ADCSRA |= (1 << ADEN); // enable ADC
}
void initTimer(void) {
	//timer1 PORTB1, PORTB2
	TCCR1A |= (1 << COM1A1); //non inverting
	TCCR1A |= (1 << WGM11);  //| (1 << WGM10);  //fast pwm 16 TOP at ICR1
	TCCR1B |= (1 << WGM13) | (1 << WGM12); 
	TCCR1B |= (1 << CS11) ;  //| (1 << CS10); //clk/8
}
int main(void)
{
	
	initTimer();
	initADC0();
	ICR1 = 39999; // =>  50hz
	DDRB |= (1 << PORTB1);	
	uint32_t adc_value;
	OCR1A = 2000	; //1800 4000
	
	while (1)
	{
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC));
		adc_value = ADC;
		adc_value = (adc_value / 1024.0) * 2600 + 1400;
		
		OCR1A = adc_value;
		
	}
}

