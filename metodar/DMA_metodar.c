//// Fil: avbrots_metodar.c   // IKKE I BRUK
//// Datamaskinkonstruksjon Høst 2017 Gruppe A
//// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
////---------------------------------------
//
////---------------------------------------
//// Inklusjonar og definisjonar
////---------------------------------------
//
//#include "stm32f30x.h"
//#include "stm32f30x_dma.h"
//#include "stm32f30x_rcc.h"
//#include "stm32f30x_usart.h"
//#include "stm32f30x_misc.h"
//
////---------------------------------------
//// Globale variablar
////---------------------------------------
//uint16_t Tester;
//
//
//#include "extern_dekl_globale_variablar.h"
//
////---------------------------------------
//// Funksjonsprototypar
////---------------------------------------
//
//void DMA1_oppstart(void);
//void DMA1_flytt(void);
//
//// Funksjonsdeklarasjonar for DMA1
////----------------------------------------------------------------------------
//void DMA1_oppstart(void) {
//
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//	DMA_InitTypeDef DMA1_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStruct;
//	DMA_DeInit(DMA1_Channel3);
//
//	DMA1_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA1_InitStructure.DMA_Mode = DMA_Mode_Circular;
//	DMA1_InitStructure.DMA_Priority = DMA_Priority_High;
//	DMA1_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	DMA1_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//	DMA1_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA1_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA1_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	DMA1_InitStructure.DMA_BufferSize = 2;
//	DMA1_InitStructure.DMA_PeripheralBaseAddr = 0x40004824; //USART3->RDR
//	DMA1_InitStructure.DMA_MemoryBaseAddr = (uint32_t)mm_DMA;
//
//
//	DMA_Init(DMA1_Channel3, &DMA1_InitStructure);
//
////	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel3_IRQn;
////	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x0;
////	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x0;
////	NVIC_Init(&NVIC_InitStruct);
//
//	DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
//	DMA_Cmd(DMA1_Channel3, ENABLE);
//
//	//inkrementer memory-adress
//	//source = 8bit byte
//	//destination = 16bit halfword
//	// fifo 1/4
//	// TCIF TCIE for avbrot
//
//	// USART3_RX = 	CH3
//
//	// Reset EN i DMA_SxCR
//	// Sett usart_rx adressen i DMA_SxPAR
//	// Sett minneadressen i DMA_SxMA0R
//	// Sett antall data i DMA_SxNDTR
//	// CHSEL[2:0] i DMA_SxCR
//	// Priority DMA_SxCR
//	// fifo 1/4
//	// Diverse i DMA_SxCR
//	// aktiver stream med EN i DMA_SxCR
//}
//
////void DMA1_Channel3_IRQHandler(void){
////
////		if (DMA1->ISR & DMA_GetFlagStatus(DMA1_FLAG_TC3)){
////		DMA_Cmd(DMA1_Channel3,DISABLE);
////		DMA1->IFCR = 0xF00;
////		Tester = mm_DMA;
////		while(DMA1_Channel3->CCR & 0x1){}
////		DMA1_Channel3->CMAR = (uint32_t)mm_DMA;
////		DMA1_Channel3->CNDTR = 0x2;
////		DMA_Cmd(DMA1_Channel3,ENABLE);
////
////		}
////}
//
