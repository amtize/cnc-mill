// Fil: avbrots_metodar.c
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------

//---------------------------------------
// Inklusjonar og definisjonar
//---------------------------------------

#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "math.h"
//---------------------------------------
// Globale variablar
//---------------------------------------

#include "extern_dekl_globale_variablar.h"

//---------------------------------------
// Funksjonsprototypar
//---------------------------------------

void avbrot_oppstart(void);
void SysTick_oppstart(void);
void SysTick_Handler(void);
void GPIO_sjekk_brytar(void);
int8_t USART3_les(void);
void PID_reguler();
void PWM_sett_vidde_TIM4_k4(uint16_t vidde);
void GPIO_brytaravprelling(void);
//---------------------------------------
// Funksjonsdeklarasjonar
//---------------------------------------

// Oppsett av avbrotssystemet
//-------------------------------------
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
  NVIC_SetPriority(SysTick_IRQn, 0); // 0-31 der 0 er høgast
  SysTick->CTRL = 0;  // Stopp teljaren
  SysTick->LOAD = 720000;  // Startverdi gir 10 msek avbrotsintervall.
  SysTick->VAL = 0;  // Nullstill teljaren
  SysTick->CTRL = (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk) ;
}
// Avbrotsmetode ("Interrupt Service Routine", ISR)
// for avbrot fraa SysTick-taimeren
//----------------------------------------------------------------

void SysTick_Handler(void) { // Hvert  10 ms
	teller_10ms++;
	if (tilstand==1){			// Dersom PÅ-tilstand
		if (teller_10ms>=10){	// Hvert 100 ms
			send_maaling=1;
			teller_10ms=0;
			tid_100ms++;
		}
		PID_reguler();
	} else {					// Dersom AV-tilstand
		teller_10ms = 0;
		paaaadrag = 0;
		LinMot_paadrag(0);
		tid_100ms=0;// Stopp
	}
	USART3_lesInnData();
	USART2_lesInnData();
}
