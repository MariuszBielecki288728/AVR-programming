#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#define _BV(bit) (1 << (bit))
#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

void initTimer(void){
	TCCR1B = (1 << CS10);
}

int testuint(void){
	
	uint8_t wynik;
	for (int k = 0; k < 10; k++){
		uint8_t i = rand();
		uint8_t j = rand() + 4235;
		
		TCNT1 = 0;
		uint8_t wyn1 = i + j;
		uint16_t time = TCNT1;
		printf("dodawanie uint8 ");
		printf("wynik: %" PRIu8 "\n", wyn1);
		printf("cykli: %" PRIu16 "\n", time);
		TCNT1 = 0;
		uint8_t wyn2 = i * j;
		time = TCNT1;
		printf("mnozenie uint8 ");
		printf("wynik: %" PRIu8 "\n", wyn2);
		printf("cykli: %" PRIu16 "\n", time);
		TCNT1 = 0;
		uint8_t wyn3 = j / i;
		time = TCNT1;
		printf("dzielenie uint8 ");
		printf("wynik: %" PRIu8 "\n", wyn3);
		printf("cykli: %" PRIu16 "\n", time);
		TCNT1 = 0;
		uint8_t wyn4 = i % j;
		time = TCNT1;
		printf("modulo uint8 ");
		printf("wynik: %" PRIu8 "\n", wyn4);
		printf("cykli: %" PRIu16 "\n", time);
		wynik += (wyn1 + wyn2 + wyn3 + wyn4);
		i++;
		j *= 2;
	}
	
	return wynik;
}
uint16_t testuin16(void){

	uint16_t wynik;

	for (int k = 0; k < 10; k++){
		uint16_t i = rand();
		uint16_t j = rand() + 42134;
		TCNT1 = 0;
		uint16_t wyn1 = j + i;
		uint16_t time = TCNT1;
		printf("dodawanie uint16 ");
		printf("wynik: %" PRIu16 "\n", wyn1);
		printf("cykli: %" PRIu16 "\n", time);
		TCNT1 = 0;
		uint16_t wyn2 = j * i;
		time = TCNT1;
		printf("mnozenie uint16 ");
		printf("wynik: %" PRIu16 "\n", wyn2);
		printf("cykli: %" PRIu16 "\n", time);
		TCNT1 = 0;
		uint16_t wyn3 = j / i;
		time = TCNT1;
		printf("dzielenie uint16 ");
		printf("wynik: %" PRIu16 "\n", wyn3);
		printf("cykli: %" PRIu16 "\n", time);
		TCNT1 = 0;
		uint16_t wyn4 = i % j;
		time = TCNT1;
		printf("modulo uint16 ");
		printf("wynik: %" PRIu16 "\n", wyn4);
		printf("cykli: %" PRIu16 "\n", time);
		wynik += (wyn1 + wyn2 + wyn3 + wyn4);
	}
	return wynik;
}
int testuin32(void){
	uint32_t wynik;
	for (int k = 0; k < 10; k++){
		uint32_t i = rand() + 1235;
		uint32_t j = rand();
		
		TCNT1 = 0;
		uint32_t wyn1 = i + j;
		uint16_t time = TCNT1;
		printf("dodawanie uint32 ");
		printf("wynik: %" PRIu32 "\n", wyn1);
		printf("cykli: %" PRIu16 "\n", time);
		
		TCNT1 = 0;
		uint32_t wyn2 = i * j;
		time = TCNT1;
		printf("mnozenie uint32 ");
		printf("wynik: %" PRIu32 "\n", wyn2);
		printf("cykli: %" PRIu16 "\n", time);
		
		TCNT1 = 0;
		uint32_t wyn3 = j / i;
		time = TCNT1;
		printf("dzielenie uint32 ");
		printf("wynik: %" PRIu32 "\n", wyn3);
		printf("cykli: %" PRIu16 "\n", time);
		
		TCNT1 = 0;
		uint32_t wyn4 = i % j;	
		time = TCNT1;
		printf("modulo uint32 ");
		printf("wynik: %" PRIu32 "\n", wyn4);
		printf("cykli: %" PRIu16 "\n", time);
		wynik += (wyn1 + wyn2 + wyn3 + wyn4);
	}
	return wynik;
}
int testfl(void){
	float wynik;
	for (int i = 0; i < 10; i++){
		float d = rand();
		float w = rand()+312;
		
		TCNT1 = 0;
		float wyn1 = w + d;
		uint16_t time = TCNT1;
		printf("dodawanie float ");
		printf("wynik: %f \n", wyn1);
		printf("cykli: %" PRIu16 "\n", time);
		
		TCNT1 = 0;
		float wyn2 = w * d;
		time = TCNT1;
		printf("mnozenie float ");
		printf("wynik: %f \n", wyn2);
		printf("cykli: %" PRIu16 "\n", time);
		
		TCNT1 = 0;
		float wyn3 = pow(w, d);
		time = TCNT1;
		printf("potegowanie float ");
		printf("wynik: %f \n", wyn3);
		printf("cykli: %" PRIu16 "\n", time);
		
		wynik += (wyn1 + wyn2 + wyn3);
		
	}
	return wynik;
}
int testdb(void){
	double wynik;
	for (int i = 0; i < 10; i++){
		double d = rand();
		double w = rand()+312;
			
		TCNT1 = 0;
		double wyn1 = w + d;
		uint16_t time = TCNT1;
		printf("dodawanie double ");
		printf("wynik: %lf \n", wyn1);
		printf("cykli: %" PRIu16 "\n", time);
		
		TCNT1 = 0;
		double wyn2 = w * d;
		time = TCNT1;
		printf("mnozenie double ");
		printf("wynik: %lf \n", wyn2);
		printf("cykli: %" PRIu16 "\n", time);
		
		TCNT1 = 0;
		double wyn3 = pow(w, d);
		time = TCNT1;
		printf("potegowanie double ");
		printf("wynik: %lf \n", wyn3);
		printf("cykli: %" PRIu16 "\n", time);
		
		wynik += (wyn1 + wyn2 + wyn3);
		
	}
	return wynik;
	
}
// inicjalizacja UART
void uart_init()
{
	// ustaw baudrate
	UBRR0 = UBRR_VALUE;
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

int main()
{
	// zainicjalizuj UART
	uart_init();
	initTimer();
	// skonfiguruj strumienie wejœcia/wyjœcia
	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
	stdin = stdout = stderr = &uart_file;
	// program testowy
	printf("Hello world!\n");
	uint32_t val = testuint();
	val += testuin16();
	val += testuin32();
	val += testdb();
	val += testfl();
	return val;
}

