/*
 * muzyka.ino
 *
 * Created: 10/28/2017 3:30:07 AM
 * Author: manie
 */ 


#include <avr/io.h>
#include <util/delay.h>
#define SPEAKER_DDR DDRD 
#define SPEAKER PORTD6
#define int8 uint8_t

#define E 99 //s
#define F 89
#define G 79
#define A 74 //s
#define B 66 //s
#define C 59
#define D 52
#define E1 49 //s
#define E1P 46
#define F1 44
#define G1 39
#define A1 37 //s
#define A1P 34
#define B1 32 //s
#define B1P 31
#define C1 29
#define P  1
static inline void initTimer(void) {
	TCCR0A |= (1 << WGM01); /* CTC mode */
	TCCR0A |= (1 << COM0A0); /* Toggles pin each cycle through */
	TCCR0B |= (1 << CS02); /* CPU clock / 256 */
}
static inline void playNote(int8 wavelength, int duration) {
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
void playSong(int8 song[], int8 dur[], int tempo){
	int length_16_note = tempo;
	for( int8 i = 0; song[i] ; i++){
		playNote(song[i], dur[i]*length_16_note);
		_delay_ms(15);
	}
}

int main(void)
{
	//TODO MOZESZ ZROBIC CO 2 WARTOSC w tablicy dlugosc

	int8 song1[] = {
		C, E1, F1, F1, E1, E1, F1, 
		F1, F1, B1, A1, G1, F1, G1, G1,
		G1, B1, C1, C1, F1, F1, E1,
		B1, B1, G1, B1, B1, B1, C1, 0};
	int8 song2[] = {
		C1, E1, F1, F1, E1, E1, F1,		           
		F1, F1, B1, A1, G1, F1, G1, G1,		
		G1, B1, C1, C1, F1, F1, E1,		
		B1, B1, G1, B1, B1, B1, C1, C1, 0
		
	 };
	 int8 song3[] = { 
		 P,  E1, B,  B,  P,  E1,		 
		 E1, F1, B,  B,  P,  B,		 
		 G1, A1, G1, F1, E1, F1,		 
		 G1, A1, G1, C,  P,  B,  C,		 
		 E1, E1, D,  D,  P,  E1, F1,		 
		 A1, G1, F1, E1, P,  F1,		 
		 G1, F1, E1P, F1, G1, A1,		 
		 G1, P, 0	 
	         };
	int8 song4[] = {
		E1, E1, D, E1, E1, D,		
		F1, F1, E1, D, C, D,		
		E1, E1, D,  F1, E1, C,		
		F1, G1, A1, B1,		
		E1, E1, D, E1, E1, D,		
		F1, F1, E1, D, E1, F1,		
		G1, A1, G1, F1, E1, F1,		
		G1, G1, A1P, B1P,0
	               //?
	};
		
	int8 dur1[] = {
		4, 4,  2,  1,  2,  1,  2,
		2,  2,  2,  2,  1,  2,  4, 1,
		4,  4,  2,  1,  2,  1,  2,
		2,  2,  2,  2,  2,  1,  13 };
	int8 dur2[] = {4,  4,  2,  1,  2,  1,  2,
				  2,  2,  2,  2,  1,  2,  4,  1,
				  4,  4,  2,  1,  2,  1,  2,
				  2,  2,  2,  2,  2,  1,  4,  1 
	};
	int8 dur3[] = {4,  2,  1,  5,  2,  2,
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
		8,  3,  3,  2};

	
	initTimer();
	/* Replace with your application code */
	while (1)
	{
		playSong(song1, dur1, 150);
		playSong(song2, dur2, 125);
		playSong(song3, dur3, 150);
		playSong(song4, dur4, 125);
	}
}

