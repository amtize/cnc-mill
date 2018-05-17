// File: GPIO_methods.c										   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//


// DIRx 	- PC2 	- DIRECTION SIGNAL FOR STEPPER MOTOR ON X-AXIS
// ENAx		- PF2	- ENABLE SIGNAL FOR STEPPER MOTOR ON X-AXIS
//
// DIRy 	- PB11 	- DIRECTION SIGNAL FOR STEPPER MOTOR ON Y-AXIS
// ENAy 	- PD13 	- ENABLE SIGNAL FOR STEPPER MOTOR ON Y-AXIS
//
// DIRz 	- PB5 	- DIRECTION SIGNAL FOR STEPPER MOTOR ON Z-AXIS
// ENAz 	- PF9 	- ENABLE SIGNAL FOR STEPPER MOTOR ON Z-AXIS
//
// DIRs		- PC9 	- DIRECTION SIGNAL FOR SPINDLE MOTOR
// ENAs		- PF6 	- ENABLE SIGNAL FOR SPINDLE MOTOR
// PWMs		- PC8

//---------------------------------------
// Includes
//---------------------------------------

#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_tim.h"
#include "math.h"

//---------------------------------------
// Variables & Functional protocols
//---------------------------------------

#include "extern_declarations_global_variables.h"




void GPIO_init(void)  {
// TypeDef
    GPIO_InitTypeDef   GPIOB_InitStructure;
    GPIO_InitTypeDef   GPIOC_InitStructure;
    GPIO_InitTypeDef   GPIOC2_InitStructure;
    GPIO_InitTypeDef   GPIOD_InitStructure;
    GPIO_InitTypeDef   GPIOF_InitStructure;
    GPIO_InitTypeDef   GPIOF2_InitStructure;

//Activate GPIO modules
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

//_________________________ GPIOB _________________________//
	// DIRz 	- PB5 	- GPIO B
	// DIRy 	- PB11 	- GPIO B
	GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_11;
	GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
	GPIOB_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOB_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIOB_InitStructure);
//_________________________________________________________//


//_________________________ GPIOC _________________________//
	// DIRx	 	- PC2 	- GPIO C
	// DIRs		- PC9 	- GPIO C
	// PWMs
	GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
	GPIOC_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOC_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIOC_InitStructure);

	GPIOC2_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;
	GPIOC2_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIOC2_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
	GPIOC2_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOC2_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIOC2_InitStructure);
//_________________________________________________________//


//_________________________ GPIOD _________________________//
	// ENAy	 	- PD13 	- GPIO D
	GPIOD_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIOD_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIOD_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
	GPIOD_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOD_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIOD_InitStructure);
//_________________________________________________________//


//_________________________ GPIOF _________________________//
	// ENAx		- PF2	- GPIO F
	// ENAz 	- PF9 	- GPIO F
	GPIOF_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_9;
	GPIOF_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIOF_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
	GPIOF_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOF_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &GPIOF_InitStructure);


	// ENAs		- PF6 	- GPIO F
	GPIOF2_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIOF2_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIOF2_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
	GPIOF2_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOF2_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIOF2_InitStructure);
//_________________________________________________________//
}
