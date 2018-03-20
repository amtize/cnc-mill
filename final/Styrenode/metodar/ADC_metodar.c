// Fil: ADC_metodar.c
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------

// Inklusjoner
#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_adc.h"
#include "stm32f30x_rcc.h"
#include "extern_dekl_globale_variablar.h"


void ADC_oppstart(void);
uint16_t ADC_convert(void);


// Initialiseringsstrukturer
GPIO_InitTypeDef GPIO_InitStructure;
ADC_InitTypeDef ADC_InitStructure;
ADC_CommonInitTypeDef ADC_CommonInitStructure;


//  Oppstart
void ADC_oppstart(void) {

//  Konfigurer klokken til ADC3 og ADC4
	RCC_ADCCLKConfig(RCC_ADC34PLLCLK_Div1);

//  Aktiverer klokken over
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC34,ENABLE);

//  Laster inn standardoppsettet fra uC (stm32f30x_adc.h/.c)
	ADC_StructInit(&ADC_InitStructure);

//  Aktiverer spenningsregulatoren på ADC3
	ADC_VoltageRegulatorCmd(ADC3,ENABLE);

//  Må vente 10us for at regulatoren blir satt opp
	for (volatile int i = 0; i < 72; i++); // 72 * 1/f_clk = 72 * (1 / (72*10^6)) = ca 11 us

//  Velger kalibreringsmetode of starter kalibrering
	ADC_SelectCalibrationMode(ADC3,ADC_CalibrationMode_Single);
	ADC_StartCalibration(ADC3);

//  Venter til kalibreringen skal bli ferdig
	while(ADC_GetCalibrationStatus(ADC3) != RESET);

// 	Setter opp ADC3 modulen med initialiseringsstruktur og laster inn vhja ADC_CommonInit();
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;
    ADC_CommonInit(ADC3, &ADC_CommonInitStructure);

//  Setter opp ADC3 med antall kanaler, oppløsning, dataoppstilling og håndtering
    ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
    ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigInjecEventEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Enable;
    ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
    ADC_InitStructure.ADC_NbrOfRegChannel = 1;

//  Laster inn ved hjelp av tilhørende metode
    ADC_Init(ADC3, &ADC_InitStructure);

//  Setter opp kanal 1 ADC3
    ADC_RegularChannelConfig(ADC3, ADC_Channel_1,1,ADC_SampleTime_1Cycles5);

//  Aktiverer ADC3
    ADC_Cmd(ADC3,ENABLE);

// Venter på klarsignal ADC3
    while(!ADC_GetFlagStatus(ADC3,ADC_FLAG_RDY));

// Setter opp GPIO B, Pin_1:
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed= GPIO_Speed_Level_1;

//Starter å lese fra ADC
    ADC_StartConversion(ADC3);
}

// AD Konvertering
uint16_t ADC_convert(void) {
	while(!ADC_GetFlagStatus(ADC3,ADC_FLAG_EOS));
	return ADC_GetConversionValue(ADC3);
}
