#include <avr/io.h>
#include <avr/delay.h>
#define int16 uint16_t
#define LED_BLUE PORTB3
#define LED_GREEN PORTB2
#define LED_RED PORTB1
#define LED_DDR DDRB
#define COMP_BLUE OCR2A
#define COMP_GREEN OCR1B
#define COMP_RED OCR1A
const int16_t expfun[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8,
	8, 8, 9, 9, 10, 10, 10, 11, 11, 12, 13, 13, 14,
	14, 15, 16, 17, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 29, 30, 31, 33, 34, 36, 38, 39, 41,
	43, 45, 47, 49, 51, 54, 56, 59, 61, 64, 67, 70,
	73, 77, 80, 84, 88, 92, 96, 100, 105, 110, 115,
	120, 125, 131, 137, 143, 150, 157, 164, 171, 179,
	187, 196, 205, 214, 224, 234, 244, 255, -1
};

void initTimer(void) {
	//timer1 PORTB1, PORTB2
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1); //non inverting
	TCCR1A |= (1 << WGM10)  | (1 << WGM12);  //fast pwm 8bit
	TCCR1B |= (1 << CS10); /* CPU clock / 1 => 31250Hz */
	//timer2 PORTB3
	TCCR2A |= (1 << COM2A1); //non inverting
	TCCR2A |= (1 << WGM20)  | (1 << WGM21);  //fast pwm 8bit
	TCCR2B |= (1 << CS20); /* CPU clock / 1 => 31250Hz */
	
}

void hsvtorgb(double *red, double *green, double *blue){
	double hue = rand()%360;
	int sat = 1;
	int val = 1;
	
	hue /= 60;
	int i = (int)hue;
	double f = hue-i;
	int p = 0;
	double q = val*(1-(sat*f));
	double t = val*(1-(sat*(1-f)));
	if (i==0) {*red=val; *green=t; *blue=p;}
	else if (i==1) {*red=q; *green=val; *blue = p;}
	else if (i==2) {*red=p; *green=val; *blue = t;}
	else if (i==3) {*red=p; *green=q; *blue = val;}
	else if (i==4) {*red=t; *green=p; *blue = val;}
	else if (i==5) {*red=val; *green=p; *blue = q;}
}

int main(void)
{	
	initTimer();
	double red;
	double green;
	double blue;	
	//set ocrs as output
	LED_DDR |= (1 << LED_BLUE) | (1 << LED_GREEN) | (1 << LED_RED);
	while (1)
	{
		int left_to_right = 1;
		hsvtorgb(&red, &green, &blue);
		for (int i=1; i;){
			if (expfun[i] == -1){
				left_to_right = 0;
				i--;
			}
			COMP_BLUE = (uint8_t)(blue * expfun[i]);
			COMP_GREEN = (uint8_t)(green *  expfun[i]);
			COMP_RED = (uint8_t)(red *  expfun[i]);
			
			if (left_to_right){
				i++;
			}
			else{
				i--;
			}
			_delay_ms(15);
			
		}
		
	}
	
	
}