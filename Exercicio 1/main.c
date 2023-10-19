#include <reg51.h>

void c51_tmr0 (void);
unsigned char state = 0;

void main (void) {
	unsigned char code mensagem[]= "Microcontrolador";
	unsigned char code *ponteiro;
	unsigned char aux = 0;
	
	ponteiro = mensagem;
	TMOD = 0X01;
	TH0 = 0xFF;
	TL0 = 0x60;
	ET0 = 1;
	EA = 1; // interrup??o habilitada
	TR0 = 1 ; // dispara timer
	
	while (1) {
		while (state != 4);
		state = 0;
		P1 = *(ponteiro+aux++);
		if (aux == 16) aux = 0;
	} // end of while
	
} //end of main

void c51_tmr0 (void) interrupt 1 {
	TL0 = 0x60;
	TH0 = 0xFF;
	state++;
} //end of c51_tmr0