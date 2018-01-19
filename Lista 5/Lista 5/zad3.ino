//TO JEST KOD DLA URZ¥DZENIA SLAVE
//KOD DLA MASTER PRZYGOTOWA£ DANIEL DUBIEL



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



volatile int8_t podana_liczba;
volatile int8_t wylosowana_liczba;
ISR(SPI_STC_vect) 
{
	
	//int8_t val = SPDR;        //odbieramy wiadomoœæ
	


	if (SPDR != 0)
	{
		//SPDR zostanie wyslane przy kolejnym zapytaniu, a wiêc gdy master wyœle 0
		if(SPDR == wylosowana_liczba)
		{
			SPDR = 2; //zgad³eœ!
			wylosowana_liczba = rand()%100;
		}
		else if(SPDR > wylosowana_liczba)
		{
			SPDR = 1; //wylosowana jest mniejsza!
		}
		else
		{
			SPDR = 3; //wylosowana jest wiêksza!
		}
		//SPDR = -1;
	}
	else
	{
		SPDR = 0;
	}
	printf("received: %" PRId8 "\n", SPDR);
	printf("los: %" PRId8 "\n", wylosowana_liczba);
	
	
}

void init_spi()
{
	DDRB = ( 1 << PORTB4 );        //Miso - wyjœcie
	SPCR = ( 1 << SPIE ) | ( 1 << SPE );    //W³¹czamy przerwania i SPI
}


int main(void)
{
	
	
	wylosowana_liczba = rand()%100;
	// zainicjalizuj UART
	uart_init();
	// skonfiguruj strumienie wej?cia/wyj?cia
	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
	stdin = stdout = stderr = &uart_file;
	DDRB = 0;
	init_spi();
	SPDR = 0;
	sei();
	//set_sleep_mode(SLEEP_MODE_IDLE);
	
	while(1)
	{
		//sleep_mode();
	}
}