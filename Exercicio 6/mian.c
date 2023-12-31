#include <reg51.h>

void c51_tmr0 (void);
unsigned char state = 0;

void main (void) {
	unsigned char code mensagem = 0xAA;
	
	TMOD = 0X01;
	TH0 = 0xEA;
	TL0 = 0x60;
	ET0 = 1;
	EA = 1; // interrup??o habilitada
	TR0 = 1 ; // dispara timer
	
	while (1) {
		P1 = ((mensagem >> state) & 1);
		if(state == 8) state = 0;
	} // end of while
	
} //end of main

void c51_tmr0 (void) interrupt 1 {
	TH0 = 0xEA;
	TL0 = 0x60;
	state++;
} //end of c51_tmr0