/*
 * termistor.ino
 *
 * Created: 11/23/2017 11:05:02 PM
 * Author: manie
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <math.h>
#define _BV(X) (1 << X)
#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

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


void initADC0(void) {
	ADMUX  |= (1 << REFS0); // ref vol on AVCC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);// ADC clock /64
	ADCSRA |= (1 << ADEN); // enable ADC
}

int main(void)
{
	// zainicjalizuj UART
	uart_init();
	// skonfiguruj strumienie wejœcia/wyjœcia
	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
	stdin = stdout = stderr = &uart_file;
	
	initADC0();
	
	uint16_t temp;
	uint16_t adc_value;
	float u;
	uint32_t imp;
	
	while (1)
	{
		ADCSRA |= (1 << ADSC); 
		while (ADCSRA & (1 << ADSC));
		adc_value = ADC;
		
		u = (adc_value * 5.0) / 1023.0; 
		imp = (u * 4700.0) / (5.0 - u); //resistance
		temp = ((uint16_t)(4456.0/(15.858 + log(imp/10400.0)))) - 273; //temperature in celcius
		printf("temp: %" PRIi16 "\n", (int16_t)temp);
		_delay_ms(100);
	}
}
//22 stopnie rezystancja 4900
//8 stopni rez 10400
// => beta = 4456.0242