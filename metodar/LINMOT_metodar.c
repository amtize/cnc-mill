// Fil: LINMOT_metodar.c
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------

#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "extern_dekl_globale_variablar.h"



void LinMot_oppstart(void){

	// Sett opp outputs

	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

    // DIR
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;

		// D9 (TX på adapter-click, velger retning)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

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
