// File: main.c												   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

//-------------------------------------------------------------//
// Include			  						   					//

#include "stm32f30x.h"
#include "stm32f3_discovery_lsm303dlhc.h"
#include "declarations_global_variables.h"
//#include "bro_code_parser.c"
#include <stdlib.h>

char *test_code = "L(100000,0,0);L(100000,100000,0);L(0,100000,0);L(0,0,0);";


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
//
//    signal_z_set_freq(800);
//    signal_z_set_dir(1);
//    signal_z_set_en(1);


    //signal_z_set_freq(800);
    while(1){

    	//Split and store the bro_codes from plain text into array of bro_codes
    	char **str;
		str = split(test_code, ';');

//		printf("Number of bro codes: ");
//		printf(str[0]);
//		printf("\n\n");

		int y = 1;
		for (; y <= atoi(str[0]); y++) { //str[0] is reserved for length of array

			//Wait for machine to become idle (!active)
			while(MACHINE_ACTIVE) {
				if (!MOTOR_X_ACTIVE && !MOTOR_Y_ACTIVE && !MOTOR_Z_ACTIVE) {
					MACHINE_ACTIVE = 0;
				}
			}

			MACHINE_ACTIVE = 1; //TODO: Set this to 0 in timer interuption handlers

			BRO_CODE *bro_code = parse(str[y]);
			MOTOR_INSTRUCTION *ptr = calculate_frequencies(bro_code);
			MOTOR_INSTRUCTION inst = *ptr;

//			printf("frequency x:%d\n", inst.freq_x);
//			printf("frequency y:%d\n", inst.freq_y);
//			printf("number of steps:%d\n", inst.num_steps);
//			printf("direction x:%d direction y:%d\n\n", inst.dir_x, inst.dir_y);

			//Set number of steps for motors
			number_of_steps_signal_x = inst.num_steps_x;
			number_of_steps_signal_y = inst.num_steps_y;
			number_of_steps_signal_z = inst.num_steps_z;

			//Set signal frequencies for motors
			signal_x_set_freq(inst.freq_x);
			signal_x_set_dir(inst.dir_x);
			signal_x_set_en(1);
			MOTOR_X_ACTIVE = 1;

			signal_y_set_freq(inst.freq_y);
			signal_y_set_dir(inst.dir_y);
			signal_y_set_en(1);
			MOTOR_Y_ACTIVE = 1;

			signal_z_set_freq(inst.freq_z);
			signal_z_set_dir(inst.dir_z);
			signal_z_set_en(1);
			MOTOR_Z_ACTIVE = 1;

			//Update current_pos (FIXME: this should be done inside timer interuption handlers)
			CURRENT_POS.x = bro_code->point.x;
			CURRENT_POS.y = bro_code->point.y;
			CURRENT_POS.z = bro_code->point.z;

			//Free previously allocated memory for motor instruction to avoid memory leakage
			free(bro_code);
			free(ptr);
		}

		free(str);

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
