#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define SCK_PORT PORTC0
#define MISO_PORT PORTC1
#define MOSI_PORT PORTC2
#define LED PORTD7


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



volatile uint8_t czy_dobrze;
volatile uint8_t to_powinno_byc;
volatile uint8_t czy_sprawdzono;
ISR(SPI_STC_vect) 
{
	uint8_t val = SPDR;        //odbieramy wiadomoœæ
	
	czy_dobrze = (val == to_powinno_byc);
	czy_sprawdzono = 1;
	printf("should be: %" PRIu8 "\n", to_powinno_byc);
	printf("received: %" PRIu8 "\n", val);

}
//komentarze pochodz¹ z kodu z wikipedii o bit bangling
void send_data(uint8_t data)
{

	// send bits 7..0
	for (int i = 0; i < 8; i++)
	{
		// set MOSI high if bit is 1, low if bit is 0
		if (data & 0x80)
			PORTC |= (1 << MOSI_PORT);
		else
			PORTC &= ~(1 << MOSI_PORT);

		// pulse clock to indicate that bit value should be read
		
		PORTC |= (1 << SCK_PORT);
		PORTC &= ~(1 << SCK_PORT);

		// shift byte left so next bit will be leftmost
		data <<= 1;
	}

}

void init_spi()
{
	DDRB = ( 1 << PORTB4 );        //Miso - wyjœcie
	SPCR = ( 1 << SPIE ) | ( 1 << SPE );    //W³¹czamy przerwania i SPI
}

int main(void)
{ //PORTC0 - SCK PORTC1 - MISO PORTC2 - MOSI
	DDRC |= (1 << SCK_PORT) | (1 << MOSI_PORT); // Miso stays on input
	DDRD |= (1 << LED);
	DDRB = 0;
	
	// zainicjalizuj UART
	uart_init();
	// skonfiguruj strumienie wej?cia/wyj?cia
	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
	stdin = stdout = stderr = &uart_file;
	
	init_spi();
	sei();
	for (uint8_t i; i < UINT8_MAX; i++){
		to_powinno_byc = i;
		send_data(i);
		while (!czy_sprawdzono);
		if(!czy_dobrze){
			PORTD |= (1 << LED);
		}
		czy_sprawdzono = 0;
	}
	while(1)
	{
	}
}