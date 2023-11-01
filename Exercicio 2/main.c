#include <reg51.h>

void serial(void); // protótipo de função
unsigned char state = 0;

void main (void) {
	unsigned char aux = 0;
	unsigned char mensagem[5];
	
	SCON = 0x40; // SCON: modo 1, 8-bit
	TMOD |= 0x20; // TMOD: timer 1, modo 2
	TH1 = 0xFD; // TH1: valor de recarga para 9600 baud; clk = 11,059 MHz
	TR1 = 1; // TR1: dispara timer
	ES = 1; EA = 1; // habilita interrupcao serial
	REN = 1;

	
	while (1) {
		while (state != 1); // aguarda interrupção serial
		state = 0; // indica atendimento interrupcao serial
		mensagem[aux] = SBUF;
		aux++;
		if (aux == 5) aux = 0;
		} // end of while
	
} // end of main

void serial(void) interrupt 4 { // especifica tratador de interrupção serial (4)
	if (TI) { // testa se buffer de transmissão vazio
		TI=0; // limpa flag
		state = 1;
	} // end of
	else if(RI){
		RI = 0;
		state = 1;
	}
} // end of serial