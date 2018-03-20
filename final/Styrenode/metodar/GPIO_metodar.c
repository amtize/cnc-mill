// Fil: GPIO_metodar.c
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------

//---------------------------------------
// Inklusjonar og definisjonar
//---------------------------------------

#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"

//---------------------------------------
// Globale variablar
//---------------------------------------

#include "extern_dekl_globale_variablar.h"

//---------------------------------------
// Funksjonsdeklarasjonar
//---------------------------------------

void GPIO_oppstart(void)  {

	  	// Oppsett av PA2 og PA3 for RS422 kommunikasjon mellom PC og styrenode
	    GPIO_InitTypeDef GPIO_InitStructure_UART2;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		// Oppsett PA2 som Tx mellom PC og styrenode
	    GPIO_InitStructure_UART2.GPIO_Pin = GPIO_Pin_2;
	    GPIO_InitStructure_UART2.GPIO_Mode  = GPIO_Mode_AF;
	    GPIO_InitStructure_UART2.GPIO_Speed = GPIO_Speed_Level_1;
	    GPIO_InitStructure_UART2.GPIO_OType = GPIO_OType_PP;
	    GPIO_Init(GPIOA, &GPIO_InitStructure_UART2); // Last inn i modul
	    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7); //Knytt pinnen til AF
	    // Oppsett PA3 smo Rx mellom PC og styrenode
	    GPIO_InitStructure_UART2.GPIO_Pin = GPIO_Pin_3;
	    GPIO_InitStructure_UART2.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_InitStructure_UART2.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	    GPIO_Init(GPIOA, &GPIO_InitStructure_UART2); // Last inn i modul
	  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7); //Knytt pinnen til AF



		// Oppsett PD8 og PD9 for RS422 kommunikasjon mellom kort
		GPIO_InitTypeDef GPIO_InitStructure_UART3;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
		// Oppsett PD8 som Tx mellom kort
	    GPIO_InitStructure_UART3.GPIO_Pin = GPIO_Pin_8;
	    GPIO_InitStructure_UART3.GPIO_Mode  = GPIO_Mode_AF;
	    GPIO_InitStructure_UART3.GPIO_Speed = GPIO_Speed_Level_1;
	    GPIO_InitStructure_UART3.GPIO_OType = GPIO_OType_PP;
	    GPIO_Init(GPIOD, &GPIO_InitStructure_UART3); // Last inn i modul
	    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_7); //Knytt pinnen til AF
	    // Oppsett PD9 som Rx mellom kort
	    GPIO_InitStructure_UART3.GPIO_Pin = GPIO_Pin_9;
	    GPIO_InitStructure_UART3.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_InitStructure_UART3.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	    GPIO_Init(GPIOD, &GPIO_InitStructure_UART3); // Last inn i modul
	  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_7); //Knytt pinnen til AF


		// Oppsett PA1 for PWM-signal til LinMot
		GPIO_InitTypeDef GPIO_InitStructure_TIM2;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); 	// Slepp til klokka
		GPIO_InitStructure_TIM2.GPIO_Pin = GPIO_Pin_1;     		//Konfigurer PA1
		GPIO_InitStructure_TIM2.GPIO_Mode = GPIO_Mode_AF; 		//Alternativ funksjon
		GPIO_InitStructure_TIM2.GPIO_Speed = GPIO_Speed_Level_1;
		GPIO_InitStructure_TIM2.GPIO_PuPd  = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &GPIO_InitStructure_TIM2); //Last inn i modul
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_1); //Knytt TIM2-pinnane til AF */

		// Oppsett PC2 for retning til LinMot
		GPIO_InitTypeDef GPIO_InitStructure_LinMot;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
		GPIO_InitStructure_LinMot.GPIO_Pin  = GPIO_Pin_2;
		GPIO_InitStructure_LinMot.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure_LinMot.GPIO_Speed = GPIO_Speed_Level_1;
		GPIO_InitStructure_LinMot.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure_LinMot.GPIO_PuPd  = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC, &GPIO_InitStructure_LinMot);
		GPIOC->ODR = GPIO_Pin_2;
}



