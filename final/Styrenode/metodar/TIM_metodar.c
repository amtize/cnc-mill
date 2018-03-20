// Fil: TIM_metodar.c
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------

//---------------------------------------
// Inklusjonar og definisjonar
//---------------------------------------

#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_tim.h"
#include "math.h"

//---------------------------------------
// Globale variablar
//---------------------------------------

#include "extern_dekl_globale_variablar.h"

//---------------------------------------
// Funksjonsdeklarasjonar
//---------------------------------------

void TIM_oppstart(void) {

	// Oppsett av TIM2 CH2 som PWM-utgang
	// Deklarasjon av initialiseringsstrukturane.
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;
	// Slepp først til klokka paa TIM2.
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	// Time base configuration
	TIM_TimeBaseStructure.TIM_Period = 0; //
	TIM_TimeBaseStructure.TIM_Prescaler = 0; // 0
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	// PWM1 Mode configuration: Channel2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM2->CCMR2 = 0x6800;
	// Aktiver til slutt TIM2
	TIM_Cmd(TIM2, ENABLE);
}


void TIM2_enable(void){
	TIM_Cmd(TIM2,ENABLE);
}
void TIM2_disable(void){
	TIM_Cmd(TIM2,DISABLE);
}

//
void PWM_sett_vidde_TIM2_CH2(uint32_t vidde)  {
	TIM2->CCR2 = vidde;
	//Output enable + ARPE = 1 (Auto reload preload enable)
	TIM2->CR1 = 0x81;
}

void PWM_sett_periode_TIM2_CH2(uint32_t periode) {

	if(periode==0){
		TIM2->ARR = 100;
		TIM2->CCR2 = 100;
		//Output enable + ARPE = 1 (Auto reload preload enable)
		TIM2->CR1 = 0x81;
	} else {
		TIM2->ARR = periode;
		TIM2->CCR2 = periode/2;
		//Output enable + ARPE = 1 (Auto reload preload enable)
		TIM2->CR1 = 0x81;
	}
}


