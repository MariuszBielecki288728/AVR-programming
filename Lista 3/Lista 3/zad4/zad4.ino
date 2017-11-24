/*
 * zad4.ino
 *
 * Created: 11/23/2017 9:44:03 PM
 * Author: manie
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
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
	ADMUX |= (1 << REFS0); // ref vol on AVCC
	ADMUX |= (1 << MUX3) | (1 << MUX2) | (1 << MUX1); //input channel on 1.1v
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);// ADC clock /64
	ADCSRA |= (1 << ADEN); //enable ADC
}

int main(void)
{
	
	
	
	// zainicjalizuj UART
	uart_init();
	// skonfiguruj strumienie wejœcia/wyjœcia
	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
	stdin = stdout = stderr = &uart_file;
	initADC0();
	DDRD |= (1 << PORTD6);
	uint16_t adc_value;
	float v_ref;

	while (1)
	{
		//heater off
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC)); 
		adc_value = ADC;
		v_ref = 1.1 * 1024 / adc_value;
		printf("milivolts~~: %" PRIi16 "\n", (int16_t)(v_ref*1000));		
		PORTD |= (1 << PORTD6); //turn heater on
		
		_delay_ms(500);
		
		//heater on
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC));
		adc_value = ADC;
		v_ref = 1.1 * 1024 / adc_value;
		printf("milivolts: %" PRIi16 "\n", (int16_t)(v_ref*1000));
		PORTD = 0; //turn heater off
		
		_delay_ms(500);
		
	}
}
