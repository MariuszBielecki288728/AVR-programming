#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRB
#define LED PORTB3
#define LED_BR OCR2A //led brightness

void initADC0(void) {
	ADMUX  |= (1 << REFS0); // ref vol on AVCC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);// ADC clock /64 
	ADCSRA |= (1 << ADEN); // enable ADC
}
void initTimer(void) {
	//timer2 PORTB3
	TCCR2A |= (1 << COM2A1); //non inverting
	TCCR2A |= (1 << WGM20)  | (1 << WGM21);  //fast pwm 8bit
	TCCR2B |= (1 << CS20); // CPU clock / 1 => 31250Hz 
}

int main(void)
{
	
	initTimer();
	initADC0();
	
	LED_DDR |= (1 << LED);
	
	uint16_t adc_value;
	float u;
	uint32_t imp;
	
	while (1)
	{
		ADCSRA |= (1 << ADSC); 
		while (ADCSRA & (1 << ADSC));
		adc_value = ADC;
		u = (adc_value * 5.0) / 1023.0;
		imp = (u * 47000.0) / (5.0 - u);
		if (imp < 3000000){
			LED_BR = ((imp / 3000000.0)*255) ;
		}else{
			LED_BR = 1;
		}
		
	}
}

