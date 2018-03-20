// Fil: UART_metodar.c
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------

//---------------------------------------
// Inklusjonar og definisjonar
//---------------------------------------

#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_usart.h"
#include "stm32f30x_misc.h"

//---------------------------------------
// Globale variablar
//---------------------------------------

#include "extern_dekl_globale_variablar.h"


// Funksjonsdeklarasjonar for USART2
//----------------------------------------------------------------------------
void USART2_oppstart(void)
{
	//Deklarasjon av initialiseringsstrukturane.
    USART_InitTypeDef USART2_InitStructure;
    USART_ClockInitTypeDef  USART2_ClockInitStructure;
    NVIC_InitTypeDef NVIC_InitStruct2;

    //Slepp til klokka
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    USART_ClockStructInit(&USART2_ClockInitStructure);
    USART_ClockInit(USART2, &USART2_ClockInitStructure);

    USART2_InitStructure.USART_BaudRate = 115200; //19200;//57600;//19200; //9600;
    USART2_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART2_InitStructure.USART_StopBits = USART_StopBits_1;
    USART2_InitStructure.USART_Parity =  USART_Parity_No ; //USART_Parity_Odd;
    USART2_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART2_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART2->CR3 |= 0x40;
    //Legg inn konfigurasjonen i modulen
    USART_Init(USART2, &USART2_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  	NVIC_InitStruct2.NVIC_IRQChannel = USART2_IRQn;
  	NVIC_InitStruct2.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_InitStruct2.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStruct2.NVIC_IRQChannelSubPriority = 0;
  	NVIC_Init(&NVIC_InitStruct2);
  	NVIC_EnableIRQ(USART2_IRQn);
  	//Aktiver så USART2
    USART_Cmd(USART2, ENABLE);
}



void USART2_skriv(uint8_t data){
    USART_SendData(USART2, (uint8_t) data); //Loop until the end of transmission
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
        {
        ;
        }
}

void USART2_send_tid_data(void) {
    int16_t data160, data161, data162, data163;
    //TID
    data160 = tid_100ms;
    data161 = data160 >> 4;
    data162 = data161 >> 4;
    data163 = data162 >> 4;
    USART2_skriv('T');            // T for tid
    USART2_skriv((uint8_t)(hex2ascii_tabell[(data163 & 0x000F)]));
    USART2_skriv((uint8_t)(hex2ascii_tabell[(data162 & 0x000F)]));
    USART2_skriv((uint8_t)(hex2ascii_tabell[(data161 & 0x000F)]));
    USART2_skriv((uint8_t)(hex2ascii_tabell[(data160 & 0x000F)]));
    //SENSOR
    data160 = data0;
    data161 = data160 >> 4;
    data162 = data161 >> 4;
    data163 = data162 >> 4;
    USART2_skriv('S');            // S for sensorverdi
    USART2_skriv((uint8_t)(hex2ascii_tabell[(data163 & 0x000F)]));
    USART2_skriv((uint8_t)(hex2ascii_tabell[(data162 & 0x000F)]));
    USART2_skriv((uint8_t)(hex2ascii_tabell[(data161 & 0x000F)]));
    USART2_skriv((uint8_t)(hex2ascii_tabell[(data160 & 0x000F)]));
    //Aks x-retning
	data160 = aks_x_retn;
	data161 = data160 >> 4;
	data162 = data161 >> 4;
	data163 = data162 >> 4;
	USART2_skriv('X');            // X for aks_x_retn
	USART2_skriv((uint8_t)(hex2ascii_tabell[(data163 & 0x000F)]));
	USART2_skriv((uint8_t)(hex2ascii_tabell[(data162 & 0x000F)]));
	USART2_skriv((uint8_t)(hex2ascii_tabell[(data161 & 0x000F)]));
	USART2_skriv((uint8_t)(hex2ascii_tabell[(data160 & 0x000F)]));
	data160 = ref_mm;
	data161 = data160 >> 4;
	data162 = data161 >> 4;
	data163 = data162 >> 4;
	USART2_skriv('R');            // R for referanse
	USART2_skriv((uint8_t)(hex2ascii_tabell[(data163 & 0x000F)]));
	USART2_skriv((uint8_t)(hex2ascii_tabell[(data162 & 0x000F)]));
	USART2_skriv((uint8_t)(hex2ascii_tabell[(data161 & 0x000F)]));
	USART2_skriv((uint8_t)(hex2ascii_tabell[(data160 & 0x000F)]));
}

void USART2_IRQHandler(void) {
	if (usart2_rx_buffer_fullt==0){
		if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE)!=RESET){
			usart2_rx_buffer[usart2_rx_buffer_skriveteller] = USART_ReceiveData(USART2);
			usart2_rx_buffer_skriveteller++;
			if(usart2_rx_buffer[0]=='s'){				// AV-tilstand
				usart2_rx_buffer_fullt=1;
				usart2_rx_buffer_skriveteller=0;
				tilstand=0;
			}
			if(usart2_rx_buffer_skriveteller == 17){	// Buffervektor full
				usart2_rx_buffer_skriveteller = 0;
				usart2_rx_buffer_fullt = 1;
			}
		}
	}
}

void USART2_lesInnData(void){
	if (usart2_rx_buffer_fullt==1){			// Dersom lesebufferet er fullt
		if (usart2_rx_buffer[0] == 'k'){tilstand=1;}	// PÅ-tilstand
		K_p = (usart2_rx_buffer[1]-48)*1000 +
			  (usart2_rx_buffer[2]-48)*100 +
			  (usart2_rx_buffer[3]-48)*10 +
			  (usart2_rx_buffer[4]-48);
		K_i = (usart2_rx_buffer[5]-48)*1000 +
			  (usart2_rx_buffer[6]-48)*100 +
			  (usart2_rx_buffer[7]-48)*10 +
			  (usart2_rx_buffer[8]-48);
		K_d = (usart2_rx_buffer[9]-48)*1000 +
			  (usart2_rx_buffer[10]-48)*100 +
			  (usart2_rx_buffer[11]-48)*10 +
			  (usart2_rx_buffer[12]-48);
		ref_mm = (usart2_rx_buffer[13]-48)*1000 +
				 (usart2_rx_buffer[14]-48)*100 +
				 (usart2_rx_buffer[15]-48)*10 +
				 (usart2_rx_buffer[16]-48);
		usart2_rx_buffer_fullt=0;
	}
}








// Funksjonsdeklarasjonar for USART3
//----------------------------------------------------------------------------
void USART3_oppstart(void)
{
  //Deklarasjon av initialiseringsstrukturane.
    USART_InitTypeDef USART3_InitStructure;
    USART_ClockInitTypeDef  USART3_ClockInitStructure;
    NVIC_InitTypeDef NVIC_InitStruct;

    //Slepp til klokka
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    USART_ClockStructInit(&USART3_ClockInitStructure);
    USART_ClockInit(USART3, &USART3_ClockInitStructure);

    USART3_InitStructure.USART_BaudRate = 				115200; //115200 //19200;//57600;//19200; //9600;
    USART3_InitStructure.USART_WordLength = 			USART_WordLength_8b;
    USART3_InitStructure.USART_StopBits = 				USART_StopBits_1;
    USART3_InitStructure.USART_Parity =  				USART_Parity_No ; //USART_Parity_Odd;
    USART3_InitStructure.USART_Mode = 					USART_Mode_Rx | USART_Mode_Tx;
    USART3_InitStructure.USART_HardwareFlowControl = 	USART_HardwareFlowControl_None;

    USART3->CR3 |= 0x40;

    //Legg inn konfigurasjonen i modulen
    USART_Init(USART3, &USART3_InitStructure);

    //Slå på globale avbrudd fra USART3
  	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);
    NVIC_EnableIRQ(USART3_IRQn);

    //Aktiver så USART1
    USART_Cmd(USART3, ENABLE);
}


void USART3_IRQHandler(void) {
	if (usart3_rx_buffer_fullt==0){
		if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE)!=RESET){
			usart3_rx_buffer[usart3_rx_buffer_skriveteller] = USART_ReceiveData(USART3);
			usart3_rx_buffer_skriveteller++;
			if(usart3_rx_buffer_skriveteller == 4){
				usart3_rx_buffer_skriveteller = 0;
				usart3_rx_buffer_fullt = 1;
			}
		}
	}
}

void USART3_lesInnData(void){
	if (usart3_rx_buffer_fullt==1){		// Dersom lesebufferet er fullt
		data0 = usart3_rx_buffer[0]<<8;			//	Sensorverdi 8-MSB
		data0 += usart3_rx_buffer[1];			//  Sensorverdi 8-LSB
		aks_x_retn = usart3_rx_buffer[2]<<8;	//  Aksellerasjon 8-MSB
		aks_x_retn += usart3_rx_buffer[3];		//  Aksellerasjon 8-LSB
		usart3_rx_buffer_fullt=0;				//  Kan nå overskrive gamle
	}											//  verdier i rx_buffer[]
}


