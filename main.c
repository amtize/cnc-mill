// File: main.c												   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

//-------------------------------------------------------------//
// Include						  						   //
#include "stm32f30x.h"
#include "stm32f3_discovery_lsm303dlhc.h"
#include "declarations_global_variables.h"



//-------------------------------------------------------------//
// Hovedprogram	//
int main(void)  {
	hardware_init();   // SCROLL DOWN
    //uint32_t teller = 1;
    //uint32_t state = 0;
    //uint16_t increment = 100;
    //TIM2->CR1 = 0x00;

//    signal_x_set_freq(2000);
//    signal_x_set_dir(0);
//    signal_x_set_en(1);


    signal_z_set_freq(800);
    signal_z_set_dir(1);
    signal_z_set_en(1);


    //signal_z_set_freq(800);
    while(1){

//    	signal_x_set_freq(800);
//    	signal_y_set_freq(800);
//    	signal_z_set_freq(800);

//
////    	if ((teller>=0)&(teller<=2000000)){state=0;}
////    	if ((teller>=2000000)&(teller<=4000000)){state=1;}
////    	if ((teller>=4000000)&(teller<=5000000)){state=2;}
////    	if (teller>=5000000){teller=0;}
//
//    	if (state==0){
//    	signal_x_set_dir(1);
//    	signal_y_set_dir(1);
//    	signal_x_set_en(1);
//    	signal_y_set_en(1);
//    	}
//    	if (state==1){
//    	signal_x_set_dir(0);
//    	signal_y_set_dir(0);
//    	signal_x_set_en(1);
//    	signal_y_set_en(1);
//    	}
//    	if (state==2){
//    	signal_x_set_dir(0);
//    	signal_y_set_dir(0);
//    	signal_x_set_en(0);
//    	signal_y_set_en(0);
//    	}

//    		//USART2_send_tid16_sensor16_data16x3();
//    	if (teller>=100000){increment+=10;teller=1;};
//
//    	if (increment==1000){increment=100;}

    }
}



void hardware_init(void){
	// Signal x
		TIM2_init();
		signal_x_set_en(0);

	// Signal y
		TIM4_init();
		signal_y_set_en(0);

	// Signal z
		TIM3_init();
		signal_z_set_en(0);

	// Signal drill
		TIM8_init();
		signal_drill_set_en(0);

	// Various init
		GPIO_init();
		EXTI_init();
}
