// Fil: main.c							//Hovedprogram
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------
//-------------------------------------------------------------//
// Include						  						   //
#include "stm32f30x.h"
#include "stm32f3_discovery_lsm303dlhc.h"
#include "dekl_globale_variablar.h"
#include "extern_dekl_globale_variablar.h"

//-------------------------------------------------------------//
// Hovedprogram						  						   //
int main(void)  {
    maskinvare_init();
    TIM2->CR1 = 0x00;
    while(1){
    	if (send_maaling==1){
    		__disable_irq();
    		USART2_send_tid_data();
    		send_maaling=0;
    		__enable_irq();
    	}
    }
}

