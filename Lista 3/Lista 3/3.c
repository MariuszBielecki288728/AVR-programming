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

//temps
#define TEMP_SETPOINT 30
#define TEMP_TOLERANCE 3

// inicjalizacja UART
void uart_init()
{
	// ustaw baudrate
	UBRR0 = UBRR_VALUE;
	// wyczy�� rejestr UCSR0A
	UCSR0A = 0;
	// w��cz odbiornik i nadajnik
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	// ustaw format 8n1
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
	// czekaj a� transmiter gotowy
	while(!(UCSR0A & _BV(UDRE0)));
	UDR0 = data;
	return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
	// czekaj a� znak dost�pny
	while (!(UCSR0A & _BV(RXC0)));
	return UDR0;
}

FILE uart_file;

void initADC0(void) {
	ADMUX |= (1 << REFS0) | (1 << REFS1); // refvol on 1.1v 
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // ADC clock /8
	ADCSRA |= (1 << ADEN); // enable ADC 
}

int main(void)
{
	uint16_t adc_value;
	int16_t temp;
	uint8_t temp_off_flag = 0;
	DDRD |= (1 << PORTD6);
	DDRB |= (1 << PORTB3);
	PORTB |= (1 << PORTB3);
	//zainicjuj adc0
	initADC0();
	// zainicjalizuj UART
	uart_init();
	// skonfiguruj strumienie wej�cia/wyj�cia
	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
	stdin = stdout = stderr = &uart_file;
	while (1)
	{	//turn heat off
		PORTD = 0;
		_delay_ms(1);
		
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC));
		adc_value = ADC;
		
		temp = (adc_value - 500) / 10;
		printf("temp: %" PRIi16 "\n", (int16_t)temp);
		
		if (temp < TEMP_SETPOINT){
			temp_off_flag = 0;
		}else if(temp >= TEMP_SETPOINT + TEMP_TOLERANCE ){
			PORTB = 0; //turn led off
			temp_off_flag = 1;
		}
		if (!temp_off_flag){
			PORTD |= (1 << PORTD6); //turn heat on
			PORTB |= (1 << PORTB3); //turn led on
		}
		_delay_ms(500);
	}
}