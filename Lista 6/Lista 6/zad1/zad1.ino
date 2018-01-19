/*
 * zad1.ino
 *
 * Created: 1/12/2018 9:32:43 PM
 * Author: manie
 */ 

int main(void)
{
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
	
	/* Replace with your application code */
	while (1)
	{
	}
}
