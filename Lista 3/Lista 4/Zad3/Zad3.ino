#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
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
	// w³¹cz przerwania na RX
	UCSR0B |= _BV(RXCIE0);
	// ustaw format 8n1 
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}


volatile char received_character;

//receive complete interrupt
ISR(USART_RX_vect)
{
	received_character = UDR0;
	UDR0 = received_character;
	//turn off this interrupt
	//UCSR0A &= ~(1 << RXC0);
	//turn on interrupt on UDRE0
	//UCSR0B |= (1 << UDRIE0);
}

//UDR ready interrupt
// ISR(USART_UDRE_vect)
// {
// 	UDR0 = received_character;
// 	//turn off interrupt on UDRE0
// 	UCSR0B &= ~(1 << UDRIE0);
// }



int main(void)
{
	uart_init();
	
	//sleep mode select - IDLE
	set_sleep_mode(SLEEP_MODE_IDLE);
	//set power reduction register
	PRR |= ~(1 << PRUSART0);
	
	// enable global interrupts
	sei();
	
	
	
	while (1)
	{
		sleep_mode();
	}
}