/*
 * Termostat.ino
 *
 * Created: 11/19/2017 3:40:19 AM
 * Author: manie
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#define _BV(X) (1 << X)
#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define TR_BASE PORTB0
#define TR_EMITTER PORTD7
#define TR_BASE_DDR DDRB
#define TR_EMITTER_DDR DDRD
// inicjalizacja UART
void uart_init()
{
	// ustaw baudrate
	UBRR0 = UBRR_VALUE;
	// wyczyœæ rejestr UCSR0A
	UCSR0A = 0;
	// w³¹cz odbiornik i nadajnik
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	// ustaw format 8n1
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
	// czekaj a¿ transmiter gotowy
	while(!(UCSR0A & _BV(UDRE0)));
	UDR0 = data;
	return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
	// czekaj a¿ znak dostêpny
	while (!(UCSR0A & _BV(RXC0)));
	return UDR0;
}

FILE uart_file;

static inline void initADC0(void) {
	ADMUX |= (1 << REFS0) | (1 << REFS1); /* reference voltage on 1.1v */
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); /* ADC clock prescaler /8 */
	ADCSRA |= (1 << ADEN); /* enable ADC */
}

int main(void)
{
	uint16_t adc_value;
	//zainicjuj adc0
	initADC0();
	// zainicjalizuj UART
	uart_init();
	// skonfiguruj strumienie wejœcia/wyjœcia
	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
	stdin = stdout = stderr = &uart_file;
	while (1)
	{
		ADCSRA |= (1 << ADSC); /* start ADC conversion */
		while (ADCSRA & (1 << ADSC));
		adc_value = ADC;
		//Pobierz wartosc na pinie A0 i zamien na napiecie, 5V max
		float temp = ( adc_value * 5.)/1023;
		//Odejmij 500mv na 0stC
		temp = temp - .5;
		//Podziel na 10mV.
		temp = temp / 0.01;
		printf("temp: %" PRIi16 "\n", (int16_t)temp);
		_delay_ms(1000);
	}
}