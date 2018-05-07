// File: interrupt_methods.c								   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

// EXTIx	- PF4	- EXTI_Line4 	- PRI 0	- SUBPRI 0	- PWM SIGNAL COUNTER FOR X-AXIS
// SOAx		- PA10	- EXTI_Line10 	- PRI 1	- SUBPRI 0	- START OF AXIS LIMIT SWITH X-AXIS
// EOAx		- PA9	- EXTI_Line9 	- PRI 1	- SUBPRI 3	- END OF AXIS LIMIT SWITH X-AXIS


// EXTIy 	- PB1	- EXTI_Line1 	- PRI 0	- SUBPRI 1	- PWM SIGNAL COUNTER FOR Y-AXIS
// SOAy		- PB8	- EXTI_Line8 	- PRI 1	- SUBPRI 1	- START OF AXIS LIMIT SWITH Y-AXIS
// EOAy		- PA15	- EXTI_Line15 	- PRI 1	- SUBPRI 4	- END OF AXIS LIMIT SWITH Y-AXIS


// EXTIz	- PC0	- EXTI_Line0 	- PRI 0	- SUBPRI 2	- PWM SIGNAL COUNTER FOR Z-AXIS
// SOAz		- PC12	- EXTI_Line12 	- PRI 1	- SUBPRI 2	- START OF AXIS LIMIT SWITH Z-AXIS
// EOAz		- PC11	- EXTI_Line11 	- PRI 1	- SUBPRI 5	- END OF AXIS LIMIT SWITH Z-AXIS


//---------------------------------------
// Inklusjonar og definisjonar
//---------------------------------------

#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "math.h"
#include "stm32f30x_exti.h"
#include "stm32f30x_syscfg.h"
#include "stm32f30x_misc.h"
//---------------------------------------
// Globale variablar
//---------------------------------------

#include "extern_declarations_global_variables.h"


void avbrot_oppstart(void) {
//     __enable_irq(); // Ikkje nødvendig. Avbrota er ope etter Reset.(PRIMASK=0)
	                   // Funksjon for stenging: __disable_irq();
     __set_BASEPRI(0x20); // Alle avbrot med prioritetsverdi 2 el. høgare blir maskert vekk (dei 4 MSb gir pri-verdien).
                          // SysTick har fått avbrotsprioritet lik 1, sjå SysTick-fila.
//     __disable_irq();
}
// Oppsett av SysTick-taimeren som realiserer fast tikk-intervall
//----------------------------------------------------------------
void SysTick_oppstart(void) {
  NVIC_SetPriority(SysTick_IRQn, 3); // 0-31 der 0 er høgast
  SysTick->CTRL = 0;  // Stopp teljaren
  SysTick->LOAD = 72000;  // Startverdi gir 1 msek avbrotsintervall.
  SysTick->VAL = 0;  // Nullstill teljaren
  SysTick->CTRL = (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk) ;
}
// Avbrotsmetode ("Interrupt Service Routine", ISR)
// for avbrot fraa SysTick-taimeren
//----------------------------------------------------------------

void SysTick_Handler(void) { // Hvert  1 ms
//	counter_1ms++;
//	if ((teller_1ms>=0)&(teller_1ms<=10000)){state=0;}
//	if ((teller_1ms>=10000)&(teller_1ms<=20000)){state=0;}
//	if ((teller_1ms>=20000)&(teller_1ms<=30000)){state=0;}
//	if (teller_1ms>=30000){teller_1ms=0;}
}

void EXTI_init(void){

// TypeDefs
	GPIO_InitTypeDef 	GPIO_EXTIx,
						GPIO_SOAx,
						GPIO_EOAx,

						GPIO_EXTIy,
						GPIO_SOAy,
						GPIO_EOAy,

						GPIO_EXTIz,
						GPIO_SOAz,
						GPIO_EOAz;

	NVIC_InitTypeDef 	NVIC_EXTIx,
						NVIC_SOAx,
						NVIC_EOAx,

						NVIC_EXTIy,
						NVIC_SOAy,
						NVIC_EOAy,

						NVIC_EXTIz,
						NVIC_SOAz,
						NVIC_EOAz;

	EXTI_InitTypeDef 	EXTI_EXTIx,
						EXTI_SOAx,
						EXTI_EOAx,

						EXTI_EXTIy,
						EXTI_SOAy,
						EXTI_EOAy,

						EXTI_EXTIz,
						EXTI_SOAz,
						EXTI_EOAz;

// ------------------------	GPIO config ------------------------ //
// Activate system clock on peripherals
	//GPIOB, GPIOC & GPIOF Already activated in "GPIO_methods.c"
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	// EXTIx	- PF4
	// SOAx		- PA10
	// EOAx		- PA9
	GPIO_EXTIx.GPIO_Mode = GPIO_Mode_IN;
	GPIO_SOAx.GPIO_Mode = GPIO_Mode_IN;
	GPIO_EOAx.GPIO_Mode = GPIO_Mode_IN;

	GPIO_EXTIx.GPIO_OType = GPIO_OType_PP;
	GPIO_SOAx.GPIO_OType = GPIO_OType_PP;
	GPIO_EOAx.GPIO_OType = GPIO_OType_PP;

	GPIO_EXTIx.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_SOAx.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_EOAx.GPIO_Speed = GPIO_Speed_Level_1;

	GPIO_EXTIx.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_SOAx.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_EOAx.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_EXTIx.GPIO_Pin = GPIO_Pin_4;
	GPIO_SOAx.GPIO_Pin = GPIO_Pin_10;
	GPIO_EOAx.GPIO_Pin = GPIO_Pin_9;

	GPIO_Init(GPIOF, &GPIO_EXTIx);
	GPIO_Init(GPIOA, &GPIO_SOAx);
	GPIO_Init(GPIOA, &GPIO_EOAx);



	// EXTIy 	- PB1
	// SOAy		- PB8
	// EOAy		- PA15
	GPIO_EXTIy.GPIO_Mode = GPIO_Mode_IN;
	GPIO_SOAy.GPIO_Mode = GPIO_Mode_IN;
	GPIO_EOAy.GPIO_Mode = GPIO_Mode_IN;

	GPIO_EXTIy.GPIO_OType = GPIO_OType_PP;
	GPIO_SOAy.GPIO_OType = GPIO_OType_PP;
	GPIO_EOAy.GPIO_OType = GPIO_OType_PP;

	GPIO_EXTIy.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_SOAy.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_EOAy.GPIO_Speed = GPIO_Speed_Level_1;

	GPIO_EXTIy.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_SOAy.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_EOAy.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_EXTIy.GPIO_Pin = GPIO_Pin_1;
	GPIO_SOAy.GPIO_Pin = GPIO_Pin_8;
	GPIO_EOAy.GPIO_Pin = GPIO_Pin_15;

	GPIO_Init(GPIOB, &GPIO_EXTIy);
	GPIO_Init(GPIOB, &GPIO_SOAy);
	GPIO_Init(GPIOA, &GPIO_EOAy);



	// EXTIz	- PC0
	// SOAz		- PC12
	// EOAz		- PC11
	GPIO_EXTIz.GPIO_Mode = GPIO_Mode_IN;
	GPIO_SOAz.GPIO_Mode = GPIO_Mode_IN;
	GPIO_EOAz.GPIO_Mode = GPIO_Mode_IN;

	GPIO_EXTIz.GPIO_OType = GPIO_OType_PP;
	GPIO_SOAz.GPIO_OType = GPIO_OType_PP;
	GPIO_EOAz.GPIO_OType = GPIO_OType_PP;

	GPIO_EXTIz.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_SOAz.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_EOAz.GPIO_Speed = GPIO_Speed_Level_1;

	GPIO_EXTIz.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_SOAz.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_EOAz.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_EXTIz.GPIO_Pin = GPIO_Pin_0;
	GPIO_SOAz.GPIO_Pin = GPIO_Pin_12;
	GPIO_EOAz.GPIO_Pin = GPIO_Pin_11;

	GPIO_Init(GPIOC, &GPIO_EXTIz);
	GPIO_Init(GPIOC, &GPIO_SOAz);
	GPIO_Init(GPIOC, &GPIO_EOAz);




// ------------------------	EXTI config ------------------------ //
	// EXTIx	- PF4
	// SOAx		- PA10
	// EOAx		- PA9
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource4); 	// Connect GPIOF Pin PF4  -> EXTI
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource10);	// Connect GPIOA Pin PA10 -> EXTI
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource9);	// Connect GPIOA Pin PA9  -> EXTI

	EXTI_EXTIx.EXTI_Line = EXTI_Line4;
	EXTI_SOAx.EXTI_Line = EXTI_Line10;
	EXTI_EOAx.EXTI_Line = EXTI_Line9;

	EXTI_EXTIx.EXTI_LineCmd = ENABLE;
	EXTI_SOAx.EXTI_LineCmd = ENABLE;
	EXTI_EOAx.EXTI_LineCmd = ENABLE;

	EXTI_EXTIx.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_SOAx.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_EOAx.EXTI_Mode = EXTI_Mode_Interrupt;

	EXTI_EXTIx.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_SOAx.EXTI_Trigger = EXTI_Trigger_Falling; 	// NC
	EXTI_EOAx.EXTI_Trigger = EXTI_Trigger_Falling;	// NC

	EXTI_Init(&EXTI_EXTIx);
	EXTI_Init(&EXTI_SOAx);
	EXTI_Init(&EXTI_EOAx);




	// EXTIy 	- PB1
	// SOAy		- PB8
	// EOAy		- PA15
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource15);

	EXTI_EXTIy.EXTI_Line = EXTI_Line1;
	EXTI_SOAy.EXTI_Line = EXTI_Line8;
	EXTI_EOAy.EXTI_Line = EXTI_Line15;

	EXTI_EXTIy.EXTI_LineCmd = ENABLE;
	EXTI_SOAy.EXTI_LineCmd = ENABLE;
	EXTI_EOAy.EXTI_LineCmd = ENABLE;

	EXTI_EXTIy.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_SOAy.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_EOAy.EXTI_Mode = EXTI_Mode_Interrupt;

	EXTI_EXTIy.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_SOAy.EXTI_Trigger = EXTI_Trigger_Falling;	// NC
	EXTI_EOAy.EXTI_Trigger = EXTI_Trigger_Falling;	// NC

	EXTI_Init(&EXTI_EXTIy);
	EXTI_Init(&EXTI_SOAy);
	EXTI_Init(&EXTI_EOAy);



	// EXTIz	- PC0
	// SOAz		- PC12
	// EOAz		- PC11
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource0); // Connect GPIOC Pin 0 -> EXTI Line0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource12);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource11);

	EXTI_EXTIz.EXTI_Line = EXTI_Line0;
	EXTI_SOAz.EXTI_Line = EXTI_Line12;
	EXTI_EOAz.EXTI_Line = EXTI_Line11;

	EXTI_EXTIz.EXTI_LineCmd = ENABLE;
	EXTI_SOAz.EXTI_LineCmd = ENABLE;
	EXTI_EOAz.EXTI_LineCmd = ENABLE;

	EXTI_EXTIz.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_SOAz.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_EOAz.EXTI_Mode = EXTI_Mode_Interrupt;

	EXTI_EXTIz.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_SOAz.EXTI_Trigger = EXTI_Trigger_Rising;	// NO
	EXTI_EOAz.EXTI_Trigger = EXTI_Trigger_Rising;	// NO

	EXTI_Init(&EXTI_EXTIz);
	EXTI_Init(&EXTI_SOAz);
	EXTI_Init(&EXTI_EOAz);




// ------------------------	NVIC config ------------------------ //
	// EXTIx	- PF4
	// SOAx		- PA10
	// EOAx		- PA9
	NVIC_EXTIx.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_SOAx.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_EOAx.NVIC_IRQChannel = EXTI9_5_IRQn;

	NVIC_EXTIx.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_SOAx.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_EOAx.NVIC_IRQChannelPreemptionPriority = 0x01;

	NVIC_EXTIx.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_SOAx.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_EOAx.NVIC_IRQChannelSubPriority = 0x03;

	NVIC_EXTIx.NVIC_IRQChannelCmd = ENABLE;
	NVIC_SOAx.NVIC_IRQChannelCmd = ENABLE;
	NVIC_EOAx.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_EXTIx);
	NVIC_Init(&NVIC_SOAx);
	NVIC_Init(&NVIC_EOAx);

	// EXTIy 	- PB1
	// SOAy		- PB8
	// EOAy		- PA15
	NVIC_EXTIy.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_SOAy.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_EOAy.NVIC_IRQChannel = EXTI15_10_IRQn;

	NVIC_EXTIy.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_SOAy.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_EOAy.NVIC_IRQChannelPreemptionPriority = 0x01;

	NVIC_EXTIy.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_SOAy.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_EOAy.NVIC_IRQChannelSubPriority = 0x04;

	NVIC_EXTIy.NVIC_IRQChannelCmd = ENABLE;
	NVIC_SOAy.NVIC_IRQChannelCmd = ENABLE;
	NVIC_EOAy.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_EXTIy);
	NVIC_Init(&NVIC_SOAy);
	NVIC_Init(&NVIC_EOAy);

	// EXTIz	- PC0
	// SOAz		- PC12
	// EOAz		- PC11
	NVIC_EXTIz.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_SOAz.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_EOAz.NVIC_IRQChannel = EXTI15_10_IRQn;

	NVIC_EXTIz.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_SOAz.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_EOAz.NVIC_IRQChannelPreemptionPriority = 0x01;

	NVIC_EXTIz.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_SOAz.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_EOAz.NVIC_IRQChannelSubPriority = 0x05;

	NVIC_EXTIz.NVIC_IRQChannelCmd = ENABLE;
	NVIC_SOAz.NVIC_IRQChannelCmd = ENABLE;
	NVIC_EOAz.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_EXTIz);
	NVIC_Init(&NVIC_SOAz);
	NVIC_Init(&NVIC_EOAz);
}

void EXTI9_5_IRQHandler(void){
	// EOAx		- PA9	- EXTI_Line9 	- PRI 1	- SUBPRI 3
	if(EXTI_GetITStatus(EXTI_Line9) != RESET){
		signal_x_set_en(0);
		counter_1ms++;
		EXTI_ClearITPendingBit(EXTI_Line9);
	}

	// SOAy		- PB8	- EXTI_Line8 	- PRI 1	- SUBPRI 1
	if(EXTI_GetITStatus(EXTI_Line8) != RESET){
		signal_y_set_en(0);
		counter_1ms++;
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}



void EXTI15_10_IRQHandler(void){
	// SOAx		- PA10	- EXTI_Line10 	- PRI 1	- SUBPRI 0
	if(EXTI_GetITStatus(EXTI_Line10) != RESET){
		signal_x_set_en(0);
		counter_1ms++;
		EXTI_ClearITPendingBit(EXTI_Line10);
	}

	// EOAy		- PA15	- EXTI_Line15 	- PRI 1	- SUBPRI 4
	if(EXTI_GetITStatus(EXTI_Line15) != RESET){
		signal_y_set_en(0);
		counter_1ms++;
		EXTI_ClearITPendingBit(EXTI_Line15);
	}

	// SOAz		- PC12	- EXTI_Line12 	- PRI 1	- SUBPRI 2
	if(EXTI_GetITStatus(EXTI_Line12) != RESET){
		signal_z_set_en(0);
		counter_1ms++;
		EXTI_ClearITPendingBit(EXTI_Line12);
	}

	// EOAz		- PC11	- EXTI_Line11 	- PRI 1	- SUBPRI 5
	if(EXTI_GetITStatus(EXTI_Line11) != RESET){
		signal_z_set_en(0);
		counter_1ms++;
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
}



void EXTI4_IRQHandler(void){
	// EXTIx	- PF4	- EXTI_Line4 	- PRI 0	- SUBPRI 0
	if(EXTI_GetITStatus(EXTI_Line4) != RESET){

		count_step_signal_x++;

		if (count_step_signal_x > number_of_steps_signal_x) {
			MOTOR_X_ACTIVE = 0;
			count_step_signal_x = 0;
			signal_x_set_en(0);
		}

		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}



void EXTI1_IRQHandler(void){
	// EXTIy 	- PB1	- EXTI_Line1 	- PRI 0	- SUBPRI 1
	if(EXTI_GetITStatus(EXTI_Line1) != RESET){
		count_step_signal_y++;

		if (count_step_signal_y > number_of_steps_signal_y) {
			MOTOR_Y_ACTIVE = 0;
			count_step_signal_y = 0;
			signal_y_set_en(0);
		}

		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}



void EXTI0_IRQHandler(void){
	// EXTIz	- PC0	- EXTI_Line0 	- PRI 0	- SUBPRI 2
	if(EXTI_GetITStatus(EXTI_Line0) != RESET){
		count_step_signal_z++;

		if (count_step_signal_z > number_of_steps_signal_z) {
			MOTOR_Z_ACTIVE = 0;
			count_step_signal_z = 0;
			signal_z_set_en(0);
		}

		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
