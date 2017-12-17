#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#define _BV(X) (1 << X)
#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem



// inicjalizacja UART
void uart_init()
{
	// ustaw baudrate
	UBRR0 = UBRR_VALUE;
	// wyczy?? rejestr UCSR0A
	UCSR0A = 0;
	// w??cz odbiornik i nadajnik
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	// ustaw format 8n1
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
	// czekaj a? transmiter gotowy
	while(!(UCSR0A & _BV(UDRE0)));
	UDR0 = data;
	return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
	// czekaj a? znak dost?pny
	while (!(UCSR0A & _BV(RXC0)));
	return UDR0;
}

FILE uart_file;



void initADC0(void) {
	ADMUX |= (1 << REFS0); // ref vol on AVCC
	ADMUX |= (1 << MUX3) | (1 << MUX2) | (1 << MUX1); //input channel on 1.1v
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) |  (1 << ADPS0);// ADC clock /128
	ADCSRA |= (1 << ADEN); // enable ADC
	
}

volatile uint16_t noise_red_res[100];
volatile uint8_t index;
volatile uint16_t active_wait_res[100];

ISR(ADC_vect)
{
	noise_red_res[index] = ADC;
	index++;
	//printf("milivolts: %" PRIu16 "\n", (uint16_t)111);
	if (index == 100){
	ADCSRA &= ~(1 << ADIE); // disable ADC interrupt
	sleep_disable();
	}
	
}

uint16_t variance(uint16_t tab[])
{
	uint32_t sum = 0;
	for (uint8_t i = 1; i<100; i++)
	{
		sum += (tab[i]*5);
	}
	uint16_t avr = sum/99;
	
	sum = 0;
	int16_t aux;
	for (uint8_t i = 1; i<100; i++)
	{
		aux = (tab[i]*5 - avr);
		sum += aux*aux;
	}
	uint16_t variance = sum / 99;
	return variance;
	
}

int main(void)
{
	index = 0;
	
	
	// zainicjalizuj UART
	uart_init();
	// skonfiguruj strumienie wej?cia/wyj?cia
	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
	stdin = stdout = stderr = &uart_file;
	initADC0();
	float adc_value;
	
	
	for (uint8_t i = 0; i<100; i++)
	{
		ADCSRA |= (1 << ADSC); //start conversion
		while (ADCSRA & (1 << ADSC));
		active_wait_res[i] = ADC;
	}
	

// 	sei();
// 	set_sleep_mode(SLEEP_MODE_ADC);
// 	while (index < 20)
// 	{
// 		ADCSRA |= (1 << ADIE); // enable ADC interrupt
// 		sleep_enable();
// 		ADCSRA |= (1 << ADSC); //start conversion
// 		do{
// 		sleep_cpu();
// 		} while (ADCSRA & (1 << ADSC));
// 		sleep_disable();
// 	}
// 	
	
	
	
	
	
	sei();
	set_sleep_mode(SLEEP_MODE_ADC);
		
	ADCSRA |= (1 << ADIE); // enable ADC interrupt
	ADCSRA |= (1 << ADATE); //enable auto trigger
	sleep_enable();
	ADCSRA |= (1 << ADSC); //start first conversion
	//for (uint8_t i = 0; i<18; i++)
	do
	{
		sleep_cpu();
	}while (index < 99);
	sleep_disable();	
	ADCSRA &= ~(1 << ADATE); // disable auto trigger

		
	printf("noise_red_res: %" PRIu16 "\n", variance(noise_red_res));
	printf("active_wait_res: %" PRIu16 "\n", variance(active_wait_res));
	
	
	
	

	while (1)
	{
		
		
	}
}
