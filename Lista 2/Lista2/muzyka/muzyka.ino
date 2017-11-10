/*
 * muzyka.ino
 *
 * Created: 10/28/2017 3:30:07 AM
 * Author: manie
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define SPEAKER_DDR DDRD 
#define SPEAKER PORTD6
#define int8 uint8_t
#define int16 uint16_t
//Nuty
#define E 99 //s (bemol)
#define F 89
#define G 79
#define A 74 //s
#define B 66 //s
#define C 59
#define D 52
#define E1 49 //s
#define E1P 46 //oryginalne E1
#define F1 44
#define G1 39
#define A1 37 //s
#define A1P 34
#define B1 32 //s
#define B1P 31
#define C1 29
#define P  1




const int8 song1[] PROGMEM = {
	C,4, E1,4, F1,3, E1,3, F1,2,
	F1,2, F1, 2, B1,2, A1,2, G1,1, F1,2, G1,5,
	G1,4, B1,4, C1,3, F1,3, E1,2,
	B1,2, B1,2, G1,2, B1,2,
B1,3, C1,13, 0};

const int8 song2[] PROGMEM = {
	C1,4, E1,4, F1,3, E1,3, F1,2,
	F1,2, F1,2, B1,2, A1,2, G1,1, F1,2, G1,5,
	G1,4, B1,4, C1,3, F1,3, E1,2,
	B1,2, B1,2, G1,2, B1,2,
B1,3, C1,5, 0};

const int8 song3[] PROGMEM = {
	P,4,  E1,2, B,1,  B,5,  P,2,  E1,2,
	E1,3, F1,3, B,2,  B,4,  P,2,  B,2,
	G1,3, A1,3, G1,2, F1,3, E1,3, F1,2,
	G1,3, A1,3, G1,1, C,4,  P,2,  B,1,  C,1,
	E1,3, E1,3, D,2,  D,4,  P,2,  E1,1, F1,1,
	A1,3, G1,3, F1,2, E1,4, P,2,  F1,2,
	G1,3, F1,3, E1P,2, F1,3, G1,3, A1,2,
	G1,12, P,4, 0
};

const int8 song4[] PROGMEM = {
	E1,3, E1,3, D,2, E1,3, E1,3, D,2,
	F1,3, F1,3, E1,2, D,3, C,3, D,2,
	E1,3, E1,3, D,2,  F1,3, E1,3, C,2,
	F1,4, G1,4, A1,4, B1,4,
	E1,3, E1,3, D,2, E1,3, E1,3, D,2,
	F1,3, F1,3, E1,2, D,3, E1,3, F1,2,
	G1,3, A1,3, G1,2, F1,3, E1,3, F1,2,
	G1,8, G1,3, A1P,3, B1P,2,
	C,4, E1,4, F1,3, E1,3, F1,2,
	F1,2, F1, 2, B1,2, A1,2, G1,1, F1,2, G1,5,
	G1,4, B1,4, C1,3, F1,3, E1,2,
	D,2, D,2, C,2, D,2, F1,1, E1,2, E1,5,
	C,4, E1,4, F1,3, E1,3, F1,2,
	F1,2, F1, 2, B1,2, A1,2, G1,1, F1,2, G1,5,
	G1,4, B1,4, C1,3, F1,3, E1,2,
	B1,2, B1,2, G1,2, B1,2, B1,3, C1,5,
	0
	
};




void initTimer(void) {
	TCCR0A |= (1 << WGM01); /* CTC mode */
	TCCR0A |= (1 << COM0A0); /* Toggles pin each cycle through */
	TCCR0B |= (1 << CS02); /* CPU clock / 256 */
}
void playNote(int8 wavelength, int16 duration) {
	if (wavelength != 1) {
		OCR0A = wavelength; /* set pitch */
		SPEAKER_DDR |= (1 << SPEAKER); /* enable output on speaker */
	}
	while (duration) { /* Variable delay */
		_delay_ms(1);
		duration--;
	}
	SPEAKER_DDR &= ~(1 << SPEAKER); /* turn speaker off */
}
void playSong( int8 *song, int16 tempo){
	int16 length_16_note = tempo;
	int8 val;
	for( int8 i = 0; val = pgm_read_byte(&(song[i])) ; i += 2){
		playNote(val, pgm_read_byte(&(song[i+1]))*length_16_note);
		_delay_ms(15);
	}
}

int main(void)
{
	//TODO MOZESZ ZROBIC CO 2 WARTOSC w tablicy dlugosc

	 
	



	
	initTimer();
	/* Replace with your application code */
	while (1)
	{
		
		
		playSong(song1, 150);
		playSong(song2, 125);
		playSong(song3, 150);
		playSong(song4, 125);
		_delay_ms(5000);
	}
}





	/*int8 dur1[] = {
		4, 4,  3,  3,  2,
		2,  2,  2,  2,  1,  2,  5,
		4,  4,  3,  3,  2,
		2,  2,  2,  2,  
		3,  13 };
	int8 dur2[] = {
		4, 4,  3,  3,  2,
		2,  2,  2,  2,  1,  2,  5,
		4,  4,  3,  3,  2,
		2,  2,  2,  2,
		3,  5 }; 
	
	int8 dur3[] = {
		4,  2,  1,  5,  2,  2,
		3,  3,  2,  4,  2,  2,
		3,  3,  2,  3,  3,  2,
		3,  3,  1,  4,  2,  1,  1,
		3,  3,  2,  4,  2,  1,  1,
		3,  3,  2,  4,  2,  2,
		3,  3,  2,  3,  3,  2,
		12, 4};
	int8 dur4[] = {
		3,  3,  2, 3,  3,  2,
		3,  3,  2, 3,  3,  2,
		3,  3,  2, 3,  3,  2,
		4,  4,  4,  4,
		3,  3,  2, 3,  3,  2,
		3,  3,  2, 3,  3,  2,
		3,  3,  2, 3,  3,  2,
		8,  3,  3,  2};*/