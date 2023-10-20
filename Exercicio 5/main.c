#include <reg51.h>

void c51_tmr0 (void);
void c51_tmr1 (void);
void c51_int1 (void);

unsigned char state = 0;

void main (void) {
	unsigned char code mensagem[]= "Microcontrolador";
	unsigned char code *ponteiro;
	unsigned char aux = 0;
	
	P2 = 0x00;
	
	ponteiro = mensagem;
	TMOD = 0X02;
	
	TH0 = 0x5F;
	TL0 = 0x5F;
	
	TH1 = 0xFC;
	TL1 = 0x3F;
	
	ET0 = 1;
	ET1 = 1;
	
	EX1 = 1;
	IT1 = 1;
	
	EA = 1; // interrup??o habilitada
	
	TR0 = 1 ; // dispara timer
	TR1 = 1;
	
	while (1) {
		while (state != 1);
		state = 0;
		P1 = *(ponteiro+aux++);
		if (aux == 16) aux = 0;
	} // end of while
	
} //end of main

void c51_tmr0 (void) interrupt 1 {
	state++;
} //end of c51_tmr0

void c51_int1 (void) interrupt 2{
	TH0 = P2;
}
void c51_tmr1 (void) interrupt 3{
	TH1 = 0xFC;
	TL1 = 0x3F;
	P2 = P2 ^ (1<<1);
}