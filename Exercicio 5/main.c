#include <reg51.h>

void serial(void); // protótipo de função
unsigned char state = 0;
unsigned char k=0;
unsigned char mensagem[10];

void main (void) {	
	unsigned char aux = 0x41;

	SCON = 0xC0; // SCON: modo 1, 8-bit
	TMOD |= 0x20; // TMOD: timer 1, modo 2
	PCON |=0x80;
	TH1 = 0xFD; // TH1: valor de recarga para 62,5 k baud; clk = 11,059 MHz
	TR1 = 1; // TR1: dispara timer
	ES = 1; EA = 1; // habilita interrupcao serial
	REN = 1;
	SBUF = aux;
	
	while (1) {
		while (state != 1); // aguarda interrupção serial
		state = 0; // indica atendimento interrupcao serial
		SBUF = aux++;
		if (aux == 0x61) aux = 0x41;
	} // end of while
	
} // end of main
void serial(void) interrupt 4 { // especifica tratador de interrupção serial (4)
	if (TI) { // testa se buffer de transmissão vazio
		TI=0; // limpa flag
		state = 1;
	} // end of if
	else if(RI){
		RI = 0;
		mensagem[k] = SBUF;
		k++;
		if(k==10) k=0;
	}
		
} // end of seria