/*
 * muzyka.ino
 *
 * Created: 10/28/2017 3:30:07 AM
 * Author: manie
 */ 


#include <avr/io.h>
#include <util/delay.h>
#define SPEAKER_DDR DDRB 
#define SPEAKER PORTB1
#define int8 uint8_t

#define E 51425 //s(b)
#define F 45814
#define G 40816
#define A 38525 //s (b)
#define B 34321 //s (b)
#define C 15288          //30577
#define D 13620          //27241
#define E1 12856 //s (b) //25712 
#define F1 11453         //22907
#define G1 10204         //20408
//#define A1 9630  //s (b) //19262

static inline void initTimer(void) {
	TCCR1A |= (1 << WGM12); /* CTC mode */
	TCCR1A |= (1 << COM1A0); /* Toggles pin each cycle through */
	TCCR1B |= (1 << CS10); /* CPU clock / 1 */
}
static inline void playNote(int wavelength, int duration) {
	if (wavelength) {
		OCR1A = wavelength; /* set pitch */
		SPEAKER_DDR |= (1 << SPEAKER); /* enable output on speaker */
	}
	while (duration) { /* Variable delay */
		_delay_ms(1);
		duration--;
	}
	SPEAKER_DDR &= ~(1 << SPEAKER); /* turn speaker off */
}
void playSong(int song[], int dur[], int tempo){
	int length_16_note = tempo;
	for( int8 i = 0; song[i] ; i++){
		playNote(song[i], dur[i]*length_16_note);
		_delay_ms(20);
	}
}

int main(void)
{
	int song[] = //{C, E1, F1, F1, E1, E1, F1, 0};
		{ E, A, C, B, A, E, D, B,
		A, C, B, G, B, E, E,
		A, C, B, A, E, G, F, F, C,
		F, E, E, E, C, A, C, 0};
		
	int dur[] = //{4, 4, 2, 1, 2, 1, 2 };
		{8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
	
	initTimer();
	/* Replace with your application code */
	while (1)
	{
		//playSong(song, dur, 150);
		_delay_ms(1000);
	}
}

