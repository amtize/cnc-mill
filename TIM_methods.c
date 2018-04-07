// File: TIM_methods.c										   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

//---------------------------------------
// Inklusjonar og definisjonar
//---------------------------------------
// Signal x 	- PA1 	- TIM2_CH2
// Signal y 	- PD12 	- TIM4_CH1
// Signal z 	- PB4 	- TIM3_CH1
// Signal drill - PC8 	- TIM8_CH3

//---------------------------------------
// Includes
//---------------------------------------

#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_tim.h"
#include "math.h"

//---------------------------------------
// Variables
//---------------------------------------

#include "extern_declarations_global_variables.h"



//__________________________ Signal x 	- PA1 	- TIM2_CH2 __________________________//
void TIM2_init(void){
	// Her er det nå TIM2 CH2 som skal brukast, og går ut på PA1.

	 //Deklarasjon av initialiseringsstrukturane.
	   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	   TIM_OCInitTypeDef        TIM_OCInitStructure;

	// Oppsett av TIM2 CH2 som PWM-utgang

	 //Slepp først til klokka paa TIM2.
	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	   /* Time base configuration */
	   TIM_TimeBaseStructure.TIM_Period = PWM_period; //
	   TIM_TimeBaseStructure.TIM_Prescaler = 71; // 0
	   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	   /* PWM1 Mode configuration: Channel2 */
	   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	   TIM_OCInitStructure.TIM_Pulse = PWM_width;
	   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	   TIM_OC2Init(TIM2, &TIM_OCInitStructure);

	//   TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

	//Så oppsett av GPIO-pinnen PA1 som blir brukt av TIM2-modulen
	//------------------------------------------
	//Deklarasjon av initialiseringsstrukturen.
		GPIO_InitTypeDef GPIO_InitStructure_TIM2;

	  //Slepp til klokka paa GPIO-portA.
		 // | RCC_AHBPeriph_AFIO

	  //Konfigurer PA1.
		GPIO_InitStructure_TIM2.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure_TIM2.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure_TIM2.GPIO_Speed = GPIO_Speed_Level_1;
		GPIO_InitStructure_TIM2.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	  //Initialiser, dvs. last ned konfigurasjonen i modulen
		GPIO_Init(GPIOA, &GPIO_InitStructure_TIM2);

	  //Knytt TIM2-pinnane til AF */
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_1); //!!!! Ikkje AF_2 som det og står i dok.

		TIM2->CCMR2 = 0x6800;

	// Aktiver til slutt TIM2
		TIM_Cmd(TIM2, ENABLE);
}

//___________________________________________________________________________________//








//__________________________ Signal y 	- PD12 	- TIM4_CH1 __________________________//

void TIM4_init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

	TIM_TimeBaseInitTypeDef TIM4_init;
	TIM4_init.TIM_Prescaler = 71;
	TIM4_init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM4_init.TIM_Period = PWM_period;
	TIM4_init.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM4, &TIM4_init);

	TIM_OCInitTypeDef TIM4_OCinit;
	TIM4_OCinit.TIM_OCMode = TIM_OCMode_PWM1;
	TIM4_OCinit.TIM_OutputState = TIM_OutputState_Enable;
	TIM4_OCinit.TIM_Pulse = PWM_width;
	TIM4_OCinit.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &TIM4_OCinit);

	GPIO_InitTypeDef TIM4_GPIOinit;
	TIM4_GPIOinit.GPIO_Pin = GPIO_Pin_12;
	TIM4_GPIOinit.GPIO_Mode = GPIO_Mode_AF;
	TIM4_GPIOinit.GPIO_Speed = GPIO_Speed_Level_1;
	TIM4_GPIOinit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &TIM4_GPIOinit);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_2);

	TIM_Cmd(TIM4, ENABLE);
}

//___________________________________________________________________________________//





//__________________________ Signal z 	- PB4 	- TIM3_CH1 __________________________//

void TIM3_init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	TIM_TimeBaseInitTypeDef TIM3_init;
	TIM3_init.TIM_Prescaler = 71;
	TIM3_init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM3_init.TIM_Period = PWM_period;
	TIM3_init.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM3, &TIM3_init);

	TIM_OCInitTypeDef TIM3_OCinit;
	TIM3_OCinit.TIM_OCMode = TIM_OCMode_PWM1;
	TIM3_OCinit.TIM_OutputState = TIM_OutputState_Enable;
	TIM3_OCinit.TIM_Pulse = PWM_width;
	TIM3_OCinit.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM3_OCinit);

	GPIO_InitTypeDef TIM3_GPIOinit;
	TIM3_GPIOinit.GPIO_Pin = GPIO_Pin_4;
	TIM3_GPIOinit.GPIO_Mode = GPIO_Mode_AF;
	TIM3_GPIOinit.GPIO_Speed = GPIO_Speed_Level_1;
	TIM3_GPIOinit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &TIM3_GPIOinit);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_2);

	TIM_Cmd(TIM3, ENABLE);
}

//___________________________________________________________________________________//





//__________________________ Signal drill - PC8	- TIM8_CH3 __________________________//

void TIM8_init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	TIM_TimeBaseInitTypeDef TIM8_init;
	TIM8_init.TIM_Prescaler = 71;
	TIM8_init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM8_init.TIM_Period = PWM_period;
	TIM8_init.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM8, &TIM8_init);

	TIM_OCInitTypeDef TIM8_OCinit;
	TIM8_OCinit.TIM_OCMode = TIM_OCMode_PWM1;
	TIM8_OCinit.TIM_OutputState = TIM_OutputState_Enable;
	TIM8_OCinit.TIM_Pulse = PWM_width;
	TIM8_OCinit.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM8, &TIM8_OCinit);

	GPIO_InitTypeDef TIM8_GPIOinit;
	TIM8_GPIOinit.GPIO_Pin = GPIO_Pin_8;
	TIM8_GPIOinit.GPIO_Mode = GPIO_Mode_AF;
	TIM8_GPIOinit.GPIO_Speed = GPIO_Speed_Level_1;
	TIM8_GPIOinit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &TIM8_GPIOinit);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_4);

	//TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	//TIM_ARRPreloadConfig(TIM8, ENABLE);
	//TIM_CtrlPWMOutputs(TIM8, ENABLE);
	TIM_Cmd(TIM8, ENABLE);
}


//___________________________________________________________________________________//
