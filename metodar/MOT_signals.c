// File: MOT_signals.c										   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

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

#include "extern_declarations_global_variables.h"




//__________________________ Signal x __________________________//


// PWM Signal x - PA1 	- TIM2_CH2
// PWM-signal adjustments. Initializations are done in "TIM_methods.c".
void signal_x_set_freq(uint16_t freq){
	TIM2->ARR = 1000000/freq - 1; 		//Period = (Timer frequency after prescaling / frequency) - 1 beacause of automatic (+ 1) addition in in STM32F303
	TIM2->CCR2 = (1000000/freq - 1)/2;
	TIM2->CR1 = 0x81;
}



// DIR Signal x - PC2 	- GPIO C
// MOT-signal adjustments. Initializations are done in "GPIO_methods.c".
void signal_x_set_dir(uint8_t dir){
	if(dir==1){
		if(GPIOC->ODR ^ GPIO_Pin_2){
		GPIOC->ODR = GPIOC->ODR | GPIO_Pin_2;
		}
	}

	if(dir==0){
		if(GPIOC->ODR & GPIO_Pin_2){
		GPIOC->ODR = GPIOC->ODR ^ GPIO_Pin_2;
		}
	}
}

// EN Signal x - PF2	- GPIO F
// MOT-signal adjustments. Initializations are done in "GPIO_methods.c".
void signal_x_set_en(uint8_t en){
	if(en==1){
		if(GPIOF->ODR ^ GPIO_Pin_2){
		GPIOF->ODR = GPIOF->ODR | GPIO_Pin_2;
		}
	}

	if(en==0){
		if(GPIOF->ODR & GPIO_Pin_2){
		GPIOF->ODR = GPIOF->ODR ^ GPIO_Pin_2;
		}
	}
}
//______________________________________________________________//








//__________________________ Signal y __________________________//
// PWM Signal x  - PD12 	- TIM4_CH1
// PWM-signal adjustments. Initializations are done in "TIM_methods.c".

void signal_y_set_freq(uint16_t freq){
	TIM4->ARR = 1000000/freq - 1; 		//Period = (Timer frequency after prescaling / frequency) - 1 (reason unknown)
	TIM4->CCR1 = (1000000/freq - 1)/2;
	TIM4->CR1 |= 0x01;
	//TIM4->CR1 = 0x81;
}


// DIR Signal y - PB11 	- GPIO B
// MOT-signal adjustments. Initializations are done in "GPIO_methods.c".
void signal_y_set_dir(uint8_t dir){
	if(dir==1){
		if(GPIOB->ODR ^ GPIO_Pin_11){
		GPIOB->ODR = GPIOB->ODR | GPIO_Pin_11;
		}
	}

	if(dir==0){
		if(GPIOB->ODR & GPIO_Pin_11){
		GPIOB->ODR = GPIOB->ODR ^ GPIO_Pin_11;
		}
	}
}

// EN Signal y - PD13 	- GPIO D
// MOT-signal adjustments. Initializations are done in "GPIO_methods.c".
void signal_y_set_en(uint8_t en){
	if(en==1){
		if(GPIOD->ODR ^ GPIO_Pin_13){
		GPIOD->ODR = GPIOD->ODR | GPIO_Pin_13;
		}
	}

	if(en==0){
		if(GPIOD->ODR & GPIO_Pin_13){
		GPIOD->ODR = GPIOD->ODR ^ GPIO_Pin_13;
		}
	}
}

//___________________________________________________________________________________//






//__________________________ Signal z __________________________//
// PWM Signal z  - PB4 	- TIM3_CH1
// PWM-signal adjustments. Initializations are done in "TIM_methods.c".
void signal_z_set_freq(uint16_t freq){
	TIM3->ARR = 1000000/freq - 1; 		//Period = (Timer frequency after prescaling / frequency) - 1 (reason unknown)
	TIM3->CCR1 = (1000000/freq - 1)/2;
	TIM3->CR1 |= 0x01;
	//TIM3->CR1 = 0x81;
}



// DIR Signal z 	- PB5 	- GPIO B
// MOT-signal adjustments. Initializations are done in "GPIO_methods.c".
void signal_z_set_dir(uint8_t dir){
	if(dir==1){
		if(GPIOB->ODR ^ GPIO_Pin_5){
		GPIOB->ODR = GPIOB->ODR | GPIO_Pin_5;
		}
	}

	if(dir==0){
		if(GPIOB->ODR & GPIO_Pin_5){
		GPIOB->ODR = GPIOB->ODR ^ GPIO_Pin_5;
		}
	}
}

// EN Signal z - PF9 	- GPIO F
// MOT-signal adjustments. Initializations are done in "GPIO_methods.c".
void signal_z_set_en(uint8_t en){
	if(en==1){
		if(GPIOF->ODR ^ GPIO_Pin_9){
		GPIOF->ODR = GPIOF->ODR | GPIO_Pin_9;
		}
	}

	if(en==0){
		if(GPIOF->ODR & GPIO_Pin_9){
		GPIOF->ODR = GPIOF->ODR ^ GPIO_Pin_9;
		}
	}
}

//___________________________________________________________________________________//







//__________________________ Signal drill __________________________//
// PWM Signal drill  - PC8 	- TIM8_CH3
// PWM-signal adjustments. Initializations are done in "TIM_methods.c".
void signal_drill_set_freq(uint16_t freq){
	TIM8->ARR = 1000000/freq - 1; 		//Period = (Timer frequency after prescaling / frequency) - 1 (reason unknown)
	TIM8->CCR1 = (1000000/freq - 1)/2;
	TIM8->CR1 |= 0x01;
	//TIM8->CR1 = 0x81;
}



// DIR Signal drill	- PC9 	- GPIO C
// MOT-signal adjustments. Initializations are done in "GPIO_methods.c".
void signal_drill_set_dir(uint8_t dir){
	if(dir==1){
		if(GPIOC->ODR ^ GPIO_Pin_9){
		GPIOC->ODR = GPIOC->ODR | GPIO_Pin_9;
		}
	}

	if(dir==0){
		if(GPIOC->ODR & GPIO_Pin_9){
		GPIOC->ODR = GPIOC->ODR ^ GPIO_Pin_9;
		}
	}
}

// EN Signal drill	- PF6 	- GPIO F
// MOT-signal adjustments. Initializations are done in "GPIO_methods.c".
void signal_drill_set_en(uint8_t en){
	if(en==1){
		if(GPIOF->ODR ^ GPIO_Pin_6){
		GPIOF->ODR = GPIOF->ODR | GPIO_Pin_6;
		}
	}

	if(en==0){
		if(GPIOF->ODR & GPIO_Pin_6){
		GPIOF->ODR = GPIOF->ODR ^ GPIO_Pin_6;
		}
	}
}

//___________________________________________________________________________________//
