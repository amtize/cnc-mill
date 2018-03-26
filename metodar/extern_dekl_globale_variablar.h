// Fil: extern_dekl_globale_variablar.h
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------------------------------------
#include "stdint.h"


//---------------------------------------
// Funksjonsprototyper
//---------------------------------------
extern void TIM2_disable(void);
extern void TIM2_enable(void);

extern void maskinvare_init(void);
extern void LinMot_paadrag(int32_t paadrag2);
extern void LinMot_bytt_retning(uint8_t retning);
extern void PWM_sett_periode_TIM2_CH2(uint32_t periode);
extern void USART3_send_dataa(uint16_t inn);
extern void PID_reguler(void);
extern void USART2_oppstart(void);
extern uint8_t USART2_Get(void);
extern void USART2_skriv(uint8_t ch);
extern uint8_t USART2_les(void);
extern void USART2_send_tid16_sensor16_data16x3(void);
extern void USART2_lesInnData(void);
extern void USART3_IRQHandler(void);
extern void USART3_lesInnData(void);

extern void TIM2_init(void);
extern void TIM3_init(void);
extern void TIM4_init(void);
extern void TIM8_init(void);

extern void signal_x_set_freq(uint16_t freq);
extern void signal_y_set_freq(uint16_t freq);
extern void signal_z_set_freq(uint16_t freq);
extern void signal_drill_set_freq(uint16_t freq);

//---------------------------------------
// Globale variablar
//---------------------------------------
extern volatile uint8_t send_maaling;
extern uint8_t usart3_rx_buffer_fullt;
extern uint8_t usart3_rx_buffer_skriveteller;
extern uint8_t usart3_rx_buffer[];

extern uint8_t usart2_rx_buffer_fullt;
extern uint8_t usart2_rx_buffer_skriveteller;
extern uint8_t usart2_rx_buffer[];

extern uint16_t teller_10ms;
extern uint16_t tid_100ms;
extern uint16_t Tester;
extern uint32_t test;
extern uint32_t test1;
extern uint16_t msblsb;
extern uint16_t msblsb2;
extern uint16_t data0;
extern uint16_t data1;
extern uint32_t data0k;
extern uint16_t data_usart3_temp1;
extern uint16_t data_usart3_temp2;
extern uint16_t data_usart2_temp1;
extern uint16_t data_usart2_temp2;
extern uint16_t data_usart2_temp3;
extern uint16_t data_usart2_temp4;
#define CHECK_BIT(var,pos) ((var) &(1<<(pos)))
extern volatile uint8_t teller_usart3;
extern volatile uint32_t teller_usart2;
extern int16_t aks_x_retn;
extern uint8_t tilstand;
extern uint8_t hex2ascii_tabell[];

// PID-Regulator
extern uint16_t ref_mm;
extern int16_t K_p;
extern int16_t K_i;
extern int16_t K_d;
extern int32_t paaaadrag;
extern int32_t avvik_mm[];
extern int32_t avvik_mm_gj;
extern int32_t avvik_mm_gjk;
extern int32_t avvik_filtert[];
extern uint8_t derivator_begrensing;
extern uint8_t integrator_antiwindup;
extern int32_t integrator_antiwindup_max;
extern int32_t d_ledd;
extern int32_t i_ledd[];
extern int32_t p_ledd;
extern uint16_t iir_a;
extern uint8_t dodtid;

extern uint16_t PWM_periode;
extern uint16_t PWM_vidde;
extern uint16_t PWM_preskalering;



