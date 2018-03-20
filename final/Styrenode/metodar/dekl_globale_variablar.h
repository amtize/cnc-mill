// Fil: dekl_globale_variablar.h
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------


//---------------------------------------
// Funksjonsprototyper
//---------------------------------------

void maskinvare_init(void);
// GPIO
void GPIO_oppstart(void);
//Avbrot
void SysTick_oppstart(void);
void SysTick_Handler(void);
void avbrot_oppstart(void);
//USART
void USART3_oppstart(void);
void USART3_IRQHandler(void);
void USART3_lesInnData(void);

void USART2_oppstart(void);
void USART2_IRQHandler(void);
void USART2_lesInnData(void);
void USART2_skriv(uint8_t ch);
void USART2_send_tid_data(void);

//Timere
void TIM_oppstart(void);
void TIM2_disable(void);
void TIM2_enable(void);
void PWM_sett_periode_TIM2_CH2(uint32_t periode);
void PWM_sett_vidde_TIM2_CH2(uint32_t vidde);

//LinMot
void LinMot_paadrag(int32_t paadrag2);
void LinMot_bytt_retning(uint8_t retning);
//Regulering
void PID_reguler(void);

//---------------------------------------
// Globale variablar
//---------------------------------------

//#define BUFFER_STR (5)
uint8_t usart3_rx_buffer_fullt = 0;
uint8_t usart3_rx_buffer_skriveteller = 0;
uint8_t usart3_rx_buffer[5];

uint8_t usart2_rx_buffer_fullt;
uint8_t usart2_rx_buffer_skriveteller;
uint8_t usart2_rx_buffer[17];

uint16_t teller_10ms;

uint32_t test=0;
uint32_t test1=0;
uint16_t mm_DMA;
volatile uint8_t teller_usart3 = 0;
volatile uint32_t teller_usart2 = 10;
float f_tabell[3000];
uint16_t msblsb = 0;
uint16_t msblsb2 = 0;
uint16_t data0 = 0;
uint32_t data0k = 0;
uint16_t data_usart3_temp1 = 0;
uint16_t data_usart3_temp2 = 0;
uint16_t data_usart2_temp1 = 0;
uint16_t data_usart2_temp2 = 0;
uint16_t data_usart2_temp3 = 0;
uint16_t data_usart2_temp4 = 0;
int16_t aks_x_retn;
uint8_t tilstand = 0;
uint8_t hex2ascii_tabell[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
#define CHECK_BIT(var,pos) ((var) &(1<<(pos)))
uint16_t tid_100ms = 0;
volatile uint8_t send_maaling = 0;
// PID
uint16_t ref_mm = 300;
int16_t K_p = 5155;//5155;
int16_t K_i = 0;//6444;
int16_t K_d = 0;
int32_t paaaadrag = 0;
int32_t avvik_mm[5] = {0,0,0,0,0};
int32_t avvik_mm_gj = 0;
int32_t avvik_mm_gjk = 0;
int32_t avvik_filtert[2] = {0,0};
uint8_t derivator_begrensing = 1;
uint8_t integrator_antiwindup = 1;
int32_t integrator_antiwindup_max = 50000;
int32_t d_ledd = 0;
int32_t i_ledd[2] = {0,0};
int32_t p_ledd = 0;
uint16_t iir_a = 862;
uint8_t dodband = 8;


// Eksempel på variabeloppsett for TIM2, kanal 2 som er sett opp som PWM-modul
//----------------------------------------------------




