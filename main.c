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
// Hovedprogram	//
int main(void)  {
    maskinvare_init();
    //uint32_t teller = 1;
    //uint16_t increment = 100;
    //TIM2->CR1 = 0x00;

    while(1){
    	signal_x_set_freq(1500);
    	signal_y_set_freq(1500);
    	signal_z_set_freq(1500);
    	signal_drill_set_freq(1500);
//    	teller++;
//
//
//
//    		//USART2_send_tid16_sensor16_data16x3();
//    	if (teller>=100000){increment+=10;teller=1;};
//
//    	if (increment==1000){increment=100;}

    }
}
