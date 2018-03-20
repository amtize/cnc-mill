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

//---------------------------------------
// Funksjonsprototypar
//---------------------------------------


void USART3_oppstart(void);
void USART3_Put(uint8_t ch);
uint8_t USART3_Get(void);
void USART3_skriv(uint8_t ch);
uint8_t USART3_les(void);
//void USART3_skriv_streng(uint8_t *streng);
void USART3_send_dataa(uint16_t adc_mm);
uint16_t motta2 = 0;


// Funksjonsdeklarasjonar for USART2
//----------------------------------------------------------------------------
void USART2_oppstart(void)
{
  //Deklarasjon av initialiseringsstrukturane.
    USART_InitTypeDef USART2_InitStructure;
    USART_ClockInitTypeDef  USART2_ClockInitStructure;
    NVIC_InitTypeDef NVIC_InitStruct2;

    // USART-delen må fiksast slik at den virkar her dvs. på STM32F3-kortet
    // der en bruker USART2 i staden for USART1 og med nye GPIO-pinnar, sjå manualen
    // på stm32f3 disc. shield samt brukarmanualen på f3-kortet.
    // Det kan også vera at strukturdefinisjonane er noko endra, sjå stm32f30x_usart.h

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


   //GPIO-delen må fiksast slik at den virkar her dvs. på STM32F3-kortet
   //På STM32F3: GPIO-pinnane PA2 og 3 brukt mot intern USART2-modul
   //------------------------------------------
  //Deklarasjon av initialiseringsstrukturen.
    GPIO_InitTypeDef GPIO_InitStructure_UART2;

  //Slepp foerst til klokka paa GPIOA-modulen
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  //Sett USART2 Tx (PA2) som AlternativFunksjon og "push-pull" (vanleg totempaale)
    GPIO_InitStructure_UART2.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure_UART2.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure_UART2.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure_UART2.GPIO_OType = GPIO_OType_PP;

  //Initialiser, dvs. last ned konfigurasjonen i modulen
    GPIO_Init(GPIOA, &GPIO_InitStructure_UART2);

  //Knytt pinnen til AF */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);// Sjå stm32f30x_gpio.h

  //Sett USART2 Rx (PA3) som flytande inngang ("input floating")
    GPIO_InitStructure_UART2.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure_UART2.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure_UART2.GPIO_PuPd  = GPIO_PuPd_NOPULL;

  //Initialiser, dvs. last ned konfigurasjonen i modulen
    GPIO_Init(GPIOA, &GPIO_InitStructure_UART2);

  //Knytt pinnen til AF */
  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  	NVIC_InitStruct2.NVIC_IRQChannel = USART2_IRQn;
  	NVIC_InitStruct2.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_InitStruct2.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStruct2.NVIC_IRQChannelSubPriority = 0;
  	NVIC_Init(&NVIC_InitStruct2);
  	NVIC_EnableIRQ(USART2_IRQn);


  //Aktiver så USART2
    USART_Cmd(USART2, ENABLE);

  //Send til slutt her velkomst via UART/USB-modul
}
//
////void USART1_skriv_streng(uint8_t *streng){
////    while( *streng != 0) {   // Skriv ut ein 0-terminert tekststreng
////    	USART1_skriv(*streng);
////    	streng++;
////    }
////}
//uint8_t USART2_Get(void)
//{
//    while ( USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET)
//        {
//        ;
//        }
//    return (uint8_t)USART_ReceiveData(USART2);
//}
//
//uint8_t USART2_les(void)
//{
//   if ( USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET)
//        {
//	   return (uint8_t)USART_ReceiveData(USART2);
//   }
//   else {
//       return (uint8_t)0x00;
//   }


void USART2_skriv(uint8_t data){
    USART_SendData(USART2, (uint8_t) data); //Loop until the end of transmission
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
        {
        ;
        }
}

void USART2_send_tid16_sensor16_data16x3(void) {
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

    // USART-delen må fiksast slik at den virkar her dvs. på STM32F3-kortet
    // der en bruker USART3 i staden for USART1 og med nye GPIO-pinnar, sjå manualen
    // på stm32f3 disc. shield samt brukarmanualen på f3-kortet.
    // Det kan også vera at strukturdefinisjonane er noko endra, sjå stm32f30x_usart.h

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


   //GPIO-delen må fiksast slik at den virkar her dvs. på STM32F3-kortet
   //På STM32F3: GPIO-pinnane PA2 og 3 brukt mot intern USART3-modul
   //------------------------------------------
  //Deklarasjon av initialiseringsstrukturen.
    GPIO_InitTypeDef GPIO_InitStructure_UART3;

  //Slepp foerst til klokka paa GPIOA-modulen
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

  //Sett USART3 Tx (PD8) som AlternativFunksjon og "push-pull" (vanleg totempaale)
    GPIO_InitStructure_UART3.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure_UART3.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure_UART3.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure_UART3.GPIO_OType = GPIO_OType_PP;



  //Initialiser, dvs. last ned konfigurasjonen i modulen
    GPIO_Init(GPIOD, &GPIO_InitStructure_UART3);

  //Knytt pinnen til AF */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_7);// Sjå stm32f30x_gpio.h

  //Sett USART3 Rx (PD9) som flytande inngang ("input floating")
    GPIO_InitStructure_UART3.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure_UART3.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure_UART3.GPIO_PuPd  = GPIO_PuPd_NOPULL;

  //Initialiser, dvs. last ned konfigurasjonen i modulen
    GPIO_Init(GPIOD, &GPIO_InitStructure_UART3);

  //Knytt pinnen til AF */
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_7);

  //Slå på globale avbrudd fra USART3
  	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);
    NVIC_EnableIRQ(USART3_IRQn);
    //USART3->CR1 |= USART_CR1_RXNEIE;

//  //Aktiver så USART1
    USART_Cmd(USART3, ENABLE);
//    USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);


  //Send til slutt her velkomst via UART/USB-modul
//	USART3_skriv_streng((uint16_t *)"--\nSTM32F3 er klar!\n\r");  // Ny linje og retur til linjestart etterpå.
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

//		if(USART3->ISR & USART_FLAG_RXNE){
//			data1 = USART_FLAG_RXNE;
//			msblsb = (uint16_t)USART_ReceiveData(USART3);
//			if (CHECK_BIT(msblsb,8)){
//				data_usart3_temp1 = (msblsb<<8)&0xFF00;
//			}
//			if ((msblsb & 0x0100)==0){ //else?
//				data_usart3_temp2 = (msblsb&0x00FF); //data0|((msblsb)&0x00FF);
//				data0 = data_usart3_temp1|data_usart3_temp2;
//				//data0&=0xFFFC;    // 0b1111 1111 1111 1100 Fjerner de 2 minst sign verdiene (støy)
//				//data0&=0xFFF8;    // 0b1111 1111 1111 1000 Fjerner de 3 minst sign verdiene (støy)		}
//	}}
//	if (USART3->ISR & USART_FLAG_RXNE){
//		teller_usart3++;
//		msblsb = USART_ReceiveData(USART3);
//		if (msblsb == 'a') {teller_usart3 = 0;} 					// Når nye data mottas
//
//		if (teller_usart3 == 1) {data_usart3_temp1 = (msblsb<<8)&0xFF00;}  // MSB sensor
//		if (teller_usart3 == 2) { 									// LSB sensor
//			data_usart3_temp2 = (msblsb&0xFF);
//			data0 = 0;
//			data0 = data_usart3_temp1|data_usart3_temp2;}

//		if (teller_usart3 == 3) {data_usart3_temp1 = (msblsb<<8)&0xFF00;}	// MSB aks. x-retning
//		if (teller_usart3 == 4) { 									// LSB aks. x-retning
//			data_usart3_temp2 = (msblsb&0xFF);
//			aks_x_retn = data_usart3_temp1|data_usart3_temp2;}

//		if (teller_usart3 == 5) {data_usart3_temp1 = (msblsb<<8);}	// MSB aks. y-retning
//		if (teller_usart3 == 6) { 									// LSB aks. y-retning
//			data_usart3_temp2 = (msblsb&0xFF);
//			aks_y_retn = data_usart3_temp1|data_usart3_temp2;}
//
//		if (teller_usart3 == 7) {data_usart3_temp1 = (msblsb<<8);}	// MSB aks. z-retning
//		if (teller_usart3 == 8) { 									// LSB aks. z-retning
//			data_usart3_temp2 = (msblsb&0xFF);
//			aks_z_retn = data_usart3_temp1|data_usart3_temp2;}
//	}

//	if(USART3->ISR & USART_FLAG_RXNE){
//		msblsb = (uint16_t)USART_ReceiveData(USART3);
//		if (CHECK_BIT(msblsb,8)){
//			data0temp = (msblsb<<8);
//		}
//		if ((msblsb & 0x0100)==0){ //else?
//			data0temp2 = (msblsb&0xFF); //data0|((msblsb)&0x00FF);
//			data0 = data0temp|data0temp2;
//			//data0&=0xFFFC;    // 0b1111 1111 1111 1100 Fjerner de 2 minst sign verdiene (støy)
//			//data0&=0xFFF8;    // 0b1111 1111 1111 1000 Fjerner de 3 minst sign verdiene (støy)
////		}
//	}
//}
////


//    if (USART3->ISR & USART_FLAG_IDLE) {
//
//        USART3->ISR &= ~USART_FLAG_IDLE;
//        DMA_Cmd(DMA1_Channel3,DISABLE);
//    }
//}

uint16_t USART3_Get16(void)
{
    while ( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
        {
        ;
        }
    motta2 = ((uint8_t)USART_ReceiveData(USART3)<<8);

    while ( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
            {
            ;
            }
    motta2 = (uint8_t)USART_ReceiveData(USART3);
    return motta2;
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


