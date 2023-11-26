#include <reg51.h>
#define TC_MODO_0 0x00
#define TC_MODO_1 0x01
#define TC_MODO_2 0x02
#define TC_MODO_3 0x03
#define TC_TMR 0x00
#define TC_CNT 0x04
#define TC_GATE_LOW 0x00
#define TC_GATE_HIGH 0x08

struct TmodInitStruct { char mode; char cntr_tmr; char gate; } Timer0, Timer1 ;
// função para inicializar Timers 0 (modo 1) e 1 (modo 2) como timers
void InitTimerFunction (void) {
	char temp;
	Timer1.mode = TC_MODO_2;
	Timer1.cntr_tmr = TC_TMR;
	Timer1.gate = TC_GATE_LOW;
	temp = (Timer1.mode | Timer1.cntr_tmr | Timer1.gate) << 4;
	Timer0.mode = TC_MODO_1;
	Timer0.cntr_tmr = TC_CNT;
	Timer0.gate = TC_GATE_HIGH;
	TMOD = temp | (Timer0.mode | Timer0.cntr_tmr | Timer0.gate);
}
// OBS: para rodar o hex gerado no Edsim 2.1.20, fazer update freq = 100
void main (void) {
	char dado_P1 = 0x80;
	// inicialização dos Timers 0 e 1 como timers nos modos 1 e 2, respectivamente
	InitTimerFunction();
	// estabelece valor de recarga -- inicia contagem do Timer 1
	TL1 = 6;
	TH1 = 6;
	TR1 = 1;
	// complementa nível lógico de P1.7 (pisca led) a cada final de contagem
	while (1) {
		while (!TF1); // polling
		TF1 = 0;
		P1 = P1^dado_P1;
	}
} // end of main