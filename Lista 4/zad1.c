#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <inttypes.h>
#include <stdlib.h>

#define LED PORTB0
#define LED_DDR DDRB
#define LED_PORT PORTB


#define _BV(x) (1 << x)
#define BAUD 9600                        // baudrate
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

void initTimer(void) {
	
	//timer1
	TCCR1B |= (1 << WGM12); // TC1 CTC  top at	OCR1A
	TCCR1B |= (1 << CS12) ; //cpu/256 
	// initialize counter
	TCNT1 = 0;
	// initialize compare value (1000ms)
	OCR1A = 62499;
	// initialize compare value (50ms)
	OCR1B = 3124;
	// enable compare interrupts
	TIMSK1 |= (1 << OCIE1A);

	
}


volatile uint8_t char_index;
volatile char* data_to_send;
// transmisja jednego znaku

ISR(USART_UDRE_vect)
{
	if (char ch = data_to_send[char_index]) {
		UDR0 = ch;
		char_index++;
	} else {
		char_index = 0;
		//wy³¹cz przerwanie na UDRE0
		UCSR0B &= ~(1 << UDRIE0);
	}
	
}

volatile uint32_t seconds_passed;

//every second
ISR(TIMER1_COMPA_vect)
{
	LED_PORT = (1 << LED);
	//turn on COMPB interrupt
	TIMSK1 |= (1 << OCIE1B);
	
	char str[21];
	sprintf(str, "%"PRIu32"", seconds_passed);
	uart_transmit_arr(str);
	
	seconds_passed++;
}

// turn off led after 0.1 second
ISR(TIMER1_COMPB_vect)
{
	LED_PORT = 0;
	//turn off COMPB interrupt
	TIMSK1 &= ~(1 << OCIE1B);
}


int uart_transmit_arr(char* data)
{
	if (!(UCSR0B & (1 << UDRIE0))) {
	data_to_send = data;
	//w³¹cz przerwanie na UDRE0
	UCSR0B |= (1 << UDRIE0);
	} else {
		return 1;
	}

}


int main(void)
{
	char_index = 0;
	seconds_passed = 0;
	uart_init();
	initTimer();
	
	//sleep mode select - IDLE
	set_sleep_mode(SLEEP_MODE_IDLE);
	//ddr setup
	LED_DDR |= (1 << LED);
	// enable global interrupts
	sei();
	
	
	
	while (1)
	{
		sleep_mode();
	}
}