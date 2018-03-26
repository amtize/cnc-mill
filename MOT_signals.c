// File: MOT_signals.c
// BSc CNC Mill
// Ove Nicolai Dalheim, Tarjei Græsdal
//---------------------------------------

//---------------------------------------
// Inklusjonar og definisjonar
//---------------------------------------

// PWM Signal x 	- PA1 	- TIM2_CH2
// DIR Signal x 	- PC2 	- GPIO C
// EN  Signal x		- PF2	- GPIO F
//
// PWM Signal y 	- PD12 	- TIM4_CH1
// DIR Signal y 	- PB11 	- GPIO B
// EN  Signal y 	- PD13 	- GPIO D
//
// PWM Signal z 	- PB4 	- TIM3_CH1
// DIR Signal z 	- PB5 	- GPIO B
// EN  Signal z 	- PF9 	- GPIO F
//
// PWM Signal drill	- PC8 	- TIM8_CH3
// DIR Signal drill	- PC9 	- GPIO C
// EN  Signal drill	- PF6 	- GPIO F
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

#include "extern_dekl_globale_variablar.h"




//__________________________ Signal x 	- PA1 	- TIM2_CH2 __________________________//

// PWM-signal adjustments. Initializations is done in "TIM_methods.c".

void signal_x_set_freq(uint16_t freq){
	TIM2->ARR = 1000000/freq - 1; 		//Period = (Timer frequency after prescaling / frequency) - 1 (reason unknown)
	TIM2->CCR2 = (1000000/freq - 1)/2;
	TIM2->CR1 = 0x81;
}

void signal_x_set_dir(boolean dir){

}
//___________________________________________________________________________________//




//__________________________ Signal y 	- PD12 	- TIM4_CH1 __________________________//

// PWM-signal adjustments. Initializations is done in "TIM_methods.c".

void signal_y_set_freq(uint16_t freq){
	TIM4->ARR = 1000000/freq - 1; 		//Period = (Timer frequency after prescaling / frequency) - 1 (reason unknown)
	TIM4->CCR1 = (1000000/freq - 1)/2;
	TIM4->CR1 |= 0x01;
	//TIM4->CR1 = 0x81;
}


//__________________________ Signal x 	- PB4 	- TIM3_CH1 __________________________//

// PWM-signal adjustments. Initializations is done in "TIM_methods.c".
void signal_z_set_freq(uint16_t freq){
	TIM3->ARR = 1000000/freq - 1; 		//Period = (Timer frequency after prescaling / frequency) - 1 (reason unknown)
	TIM3->CCR1 = (1000000/freq - 1)/2;
	TIM3->CR1 |= 0x01;
	//TIM3->CR1 = 0x81;
}


//__________________________ Signal x 	- PC8 	- TIM8_CH3 __________________________//

// PWM-signal adjustments. Initializations is done in "TIM_methods.c".
void signal_drill_set_freq(uint16_t freq){
	TIM8->ARR = 1000000/freq - 1; 		//Period = (Timer frequency after prescaling / frequency) - 1 (reason unknown)
	TIM8->CCR1 = (1000000/freq - 1)/2;
	TIM8->CR1 |= 0x01;
	//TIM8->CR1 = 0x81;
}
