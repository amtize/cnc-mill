// Fil: LINMOT_metodar.c
// Datamaskinkonstruksjon H�st 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond L�vik, Martin Rygg
//---------------------------------------

#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "extern_dekl_globale_variablar.h"


void LinMot_bytt_retning(uint8_t retning){
	if(retning==1){
		GPIOC->ODR = GPIO_Pin_2;
	}
	if(retning==0){
		GPIOC->ODR = 0x0;
	}

}

void LinMot_paadrag(int32_t paadrag2){
	//test1 = paadrag2;
	if (paadrag2 < -500000){ paadrag2 = -500000;};
	if (paadrag2 >  500000){ paadrag2 =  500000;};
	if (paadrag2 < 0) {
		LinMot_bytt_retning(0);
		paadrag2 = -paadrag2;
	} else {
		LinMot_bytt_retning(1);
	}
	if (paadrag2==0){
		TIM2_disable();
	} else {
		TIM2_enable();
 		PWM_sett_periode_TIM2_CH2( (uint32_t)(72000000/paadrag2) );
	}

}
