#include <reg51.h>

#define SR_MODO_0           0x00
#define SR_MODO_1           0x40
#define SR_MODO_2           0x80
#define SR_MODO_3           0xC0

#define SR_RECEIVING_HIGH   0x10
#define SR_RECEIVING_LOW    0x00

#define SR_MULTI_HIGH       0x20
#define SR_MULTI_LOW        0x00

#define SR_TRANS_BIT_HIGH   0x04
#define SR_TRANS_BIT_LOW    0x00

#define SR_REC_BIT_HIGH     0x08
#define SR_REC_BIT_LOW      0x00

#define SR_SMOD_HIGH        0xC0
#define SR_SMOD_LOW         0x00


struct SconInitStruct{ char mode; char receiving; char multiprocessing; 
                       char rec_ninth; char trans_ninth; char reload_val; 
                       char smod; char timer1_mode;} Serial;

void InitSerialFunction(void){
	Serial.mode = SR_MODO_1;
	Serial.receiving = SR_RECEIVING_LOW;
	Serial.multiprocessing = SR_MULTI_LOW;
	Serial.trans_ninth = SR_TRANS_BIT_LOW;
	Serial.rec_ninth = SR_REC_BIT_LOW;
	Serial.smod = SR_SMOD_HIGH;
	SCON = Serial.mode|Serial.receiving|Serial.multiprocessing|Serial.trans_ninth|Serial.rec_ninth;
	
	PCON = Serial.smod;
	
	Serial.reload_val = 0xFD;
	Serial.timer1_mode = 0x20;
	TMOD = Serial.timer1_mode;
	TH1 = Serial.reload_val;
	TR1 = 1;
	
	
}

void main(void){
	InitSerialFunction();
	while(1);
	
}
