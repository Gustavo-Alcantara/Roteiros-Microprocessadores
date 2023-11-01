#include <reg51.h>

void serial(void); // prot?tipo de fun??o

unsigned char state = 0;

void main (void) {
unsigned char code mensagem[]= "Microcontrolador";
unsigned char code *ponteiro;
unsigned char aux = 1;

						ponteiro=mensagem;
						SCON = 0xC0; // 1100 0000B -- SCON: modo 3, 9-bit
						TMOD = 0x20; // 0010 0000B => TMOD: timer 1, modo 2
						TH1 = 0xFD; // TH1: valor de recarga para 9600 baud; clk = 11,059 MHz
						TR1 = 1; // TR1: dispara timer
						ES = 1;
						EA = 1; // habilita interrupcao serial
						ACC = *ponteiro; // envia 'M'
						TB8 = P;
						SBUF = ACC;
	
						while (1) {
										while (state != 1); // aguarda interrup??o serial
										state = 0; // indica atendimento interrupcao serial
										ACC = *(ponteiro+aux++);
										TB8 = P;
										SBUF = ACC;
										if (aux == 16) aux = 0;
						} // end of while
						} // end of main
						
void serial(void) interrupt 4 { // especifica tratador de interrup??o serial (4)
				if (TI) { // testa se buffer de transmiss?o vazio
																	TI=0; // limpa flag
																	state = 1;
				} // end of if
} // end of serial