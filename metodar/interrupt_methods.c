// File: interrupt_methods.c								   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

// EXTI_Pin signal x	PF4
// EXTI_Pin	signal y 	PB1
// EXTI_Pin signal z	PC0

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

// TypeDef
	GPIO_InitTypeDef GPIO_EXTI_signal_x, 	GPIO_EXTI_signal_y, GPIO_EXTI_signal_z;
	NVIC_InitTypeDef NVIC_EXTI_signal_x, 	NVIC_EXTI_signal_y, NVIC_EXTI_signal_z;
	EXTI_InitTypeDef EXTI_signal_x, 		EXTI_signal_y, 		EXTI_signal_z;

// Activate system clock on peripherals
	//GPIOB, GPIOC & GPIOF Already activated in "GPIO_methods.c"
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

// GPIO config
	// EXTI_Pin signal x	PF4
	GPIO_EXTI_signal_x.GPIO_Mode = GPIO_Mode_IN;
	GPIO_EXTI_signal_x.GPIO_OType = GPIO_OType_PP;
	GPIO_EXTI_signal_x.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_EXTI_signal_x.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_EXTI_signal_x.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOF, &GPIO_EXTI_signal_x);

	// EXTI_Pin	signal y 	PB1
	GPIO_EXTI_signal_y.GPIO_Mode = GPIO_Mode_IN;
	GPIO_EXTI_signal_y.GPIO_OType = GPIO_OType_PP;
	GPIO_EXTI_signal_y.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_EXTI_signal_y.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_EXTI_signal_y.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_EXTI_signal_y);

	// EXTI_Pin signal z	PC0
	GPIO_EXTI_signal_z.GPIO_Mode = GPIO_Mode_IN;
	GPIO_EXTI_signal_z.GPIO_OType = GPIO_OType_PP;
	GPIO_EXTI_signal_z.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_EXTI_signal_z.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_EXTI_signal_z.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOC, &GPIO_EXTI_signal_z);





// EXTI config
	// EXTI_Pin signal x	PF4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource4); // Connect GPIOF Pin 4 -> EXTI Line4
	EXTI_signal_x.EXTI_Line = EXTI_Line4;
	EXTI_signal_x.EXTI_LineCmd = ENABLE;
	EXTI_signal_x.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_signal_x.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_signal_x);

	// EXTI_Pin	signal y 	PB1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1); // Connect GPIOF Pin 4 -> EXTI Line4
	EXTI_signal_y.EXTI_Line = EXTI_Line1;
	EXTI_signal_y.EXTI_LineCmd = ENABLE;
	EXTI_signal_y.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_signal_y.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_signal_y);

	// EXTI_Pin signal z	PC0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource0); // Connect GPIOF Pin 4 -> EXTI Line4
	EXTI_signal_z.EXTI_Line = EXTI_Line0;
	EXTI_signal_z.EXTI_LineCmd = ENABLE;
	EXTI_signal_z.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_signal_z.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_signal_z);





// NVIC config
	// EXTI_Pin signal x	PF4
	NVIC_EXTI_signal_x.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_EXTI_signal_x.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_EXTI_signal_x.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_EXTI_signal_x.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_EXTI_signal_x);

	// EXTI_Pin	signal y 	PB1
	NVIC_EXTI_signal_y.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_EXTI_signal_y.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_EXTI_signal_y.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_EXTI_signal_y.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_EXTI_signal_y);

	// EXTI_Pin signal z	PC0
	NVIC_EXTI_signal_z.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_EXTI_signal_z.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_EXTI_signal_z.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_EXTI_signal_z.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_EXTI_signal_z);
}

void EXTI4_IRQHandler(void){
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
