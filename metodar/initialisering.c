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
volatile uint16_t push;
//---------------------------------------
// Funksjonsprototypar
//---------------------------------------

void maskinvare_init(void);
void GPIO_oppstart(void);
//void PID_oppstart();
void USART2_oppstart(void);
void ADC_oppstart();
void SysTick_oppstart(void);
void USART3_oppstart(void);
void TIM_oppstart(void);
void TIM4_oppstart_reg(void);
void SPI1_oppstart(void);
void SPI2_oppstart(void);
void Exp_click_sokkel1_oppstart(void);
void LinMot_oppstart(void);
void aks_oppstart(void);
void gyro_oppstart(void);
void avbrot_oppstart(void);
void Lag_Tabell(void);
//void DMA1_oppstart(void);
void LinMot_paadrag(int32_t paadrag2);


//---------------------------------------
// Funksjonsdeklarasjonar
//---------------------------------------

void maskinvare_init(void) {

	GPIO_oppstart();
//	GPIO_1oppstart();
	SysTick_oppstart();
	avbrot_oppstart();
	USART3_oppstart();
	USART2_oppstart();
	TIM_oppstart();
	Lag_Tabell();
	TIM4_oppstart_reg();
	ADC_oppstart();
	//LinMot_paadrag(0);


}





