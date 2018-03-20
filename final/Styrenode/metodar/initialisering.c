// Fil: initialisering.c
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------

//---------------------------------------
// Inklusjonar og definisjonar
//---------------------------------------

#include "stm32f30x.h"
#include "stm32f3_discovery_lsm303dlhc.h"
#include "extern_dekl_globale_variablar.h"
//---------------------------------------
// Funksjonsprototypar
//---------------------------------------




//---------------------------------------
// Funksjonsdeklarasjonar
//---------------------------------------

void maskinvare_init(void) {

	GPIO_oppstart();
	SysTick_oppstart();
	USART3_oppstart();
	USART2_oppstart();
	TIM_oppstart();
	avbrot_oppstart();
	LinMot_paadrag(0);

}





