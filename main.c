// File: main.c												   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

//-------------------------------------------------------------//
// Include			  						   					//

#include "stm32f30x.h"
#include "stm32f3_discovery_lsm303dlhc.h"
#include "declarations_global_variables.h"
//#include "UART_metodar.c"
//#include "bro_code_parser.c"
#include <stdlib.h>


//char *test_code = "L(1000,0,0);L(1000,1000,0);";//"L(101,99,0);L(101,898,10);L(904,898,10);L(904,99,10);L(904,99,10);L(102,100,10);L(102,100,10);L(102,896,10);L(902,896,10);L(902,100,10);L(902,100,0);L(103,101,0);L(103,101,10);L(103,894,10);L(900,894,10);L(900,101,10);L(900,101,0);L(104,102,0);L(104,102,10);L(104,892,10);L(898,892,10);L(898,102,10);L(898,102,0);L(105,103,0);L(105,103,10);L(105,890,10);L(896,890,10);L(896,103,10);L(896,103,0);L(106,104,0);L(106,104,10);L(106,888,10);L(894,888,10);L(894,104,10);L(894,104,0);L(107,105,0);L(107,105,10);L(107,886,10);L(892,886,10);L(892,105,10);L(892,105,0);L(108,106,0);L(108,106,10);L(108,884,10);L(890,884,10);L(890,106,10);L(890,106,0);L(109,107,0);L(109,107,10);L(109,882,10);L(888,882,10);L(888,107,10);L(888,107,0);L(110,108,0);L(110,108,10);L(110,880,10);L(886,880,10);L(886,108,10);L(886,108,0);L(111,109,0);L(111,109,10);L(111,878,10);L(884,878,10);L(884,109,10);L(884,109,0);L(112,110,0);L(112,110,10);L(112,876,10);L(882,876,10);L(882,110,10);L(882,110,0);L(113,111,0);L(113,111,10);";

//-------------------------------------------------------------//
// Hovedprogram	//
int main(void)  {
	hardware_init();   // SCROLL DOWN

	USART2_oppstart();
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


	//signal_drill_set_dir(0);
	//signal_drill_set_freq(100);
	//signal_drill_set_en(1);

	while(MACHINE_STATE == 0) {
		;
	}

	while(1) {

		while(MACHINE_ACTIVE == 1) {
			if (END_STOP_ENGAGED == 1) {
				MACHINE_ACTIVE = 0;
				usart_send_string("END_STOP\n");
				handle_end_stop();
				break;
			}

			if ((MOTOR_X_ACTIVE == 0) && (MOTOR_Y_ACTIVE == 0) && (MOTOR_Z_ACTIVE == 0) ) {
				MACHINE_ACTIVE = 0;
				// Notify supervisory control system that I am ready
				usart_send_string("R\n");
			}
		}


		while(BRO_CODE_BUFFERED == 0){
			; //Wait for bro-code from supervisory control system
		}

		BRO_CODE_BUFFERED = 0;

		BRO_CODE *bro_code = parse(test_code);

		if (bro_code->cmd == Off) {
			signal_drill_set_en(0);
			signal_x_set_en(0);
			signal_y_set_en(0);
			signal_z_set_en(0);
			continue;
		}

		MOTOR_INSTRUCTION *ptr = calculate_frequencies(bro_code);
		MOTOR_INSTRUCTION inst = *ptr;



		number_of_steps_signal_x = inst.num_steps_x;
		number_of_steps_signal_y = inst.num_steps_y;
		number_of_steps_signal_z = inst.num_steps_z;

		//Set signal frequencies for motors

		if (inst.num_steps_x > 0) {
			signal_x_set_freq(inst.freq_x);
			signal_x_set_dir(inst.dir_x);
			signal_x_set_en(1);
			MOTOR_X_ACTIVE = 1;
			count_step_signal_x = 0;

			MACHINE_ACTIVE = 1;
		} else {
		}

		if (inst.num_steps_y > 0) {
			signal_y_set_freq(inst.freq_y);
			signal_y_set_dir(inst.dir_y);
			signal_y_set_en(1);
			MOTOR_Y_ACTIVE = 1;
			count_step_signal_y = 0;

			MACHINE_ACTIVE = 1;
		} else {
		}

		if (inst.num_steps_z > 0) {
			signal_z_set_freq(inst.freq_z);
			signal_z_set_dir(inst.dir_z);
			signal_z_set_en(1);
			MOTOR_Z_ACTIVE = 1;
			count_step_signal_z = 0;

			MACHINE_ACTIVE = 1;
		} else {
		}

		 //TODO: Set this to 0 in timer interuption handlers

		MACHINE_ACTIVE = 1;
		//Update current_pos (FIXME: this should be done inside timer interuption handlers)
		CURRENT_POS.x = bro_code->point.x;
		CURRENT_POS.y = bro_code->point.y;
		CURRENT_POS.z = bro_code->point.z;

		free(bro_code);
		free(ptr);
	}



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
			while(MACHINE_ACTIVE == 1) {
				if ((MOTOR_X_ACTIVE == 0) && (MOTOR_Y_ACTIVE == 0) && (MOTOR_Z_ACTIVE == 0) ) {
					MACHINE_ACTIVE = 0;
				}
			}


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

			if (inst.num_steps_x > 0) {
				signal_x_set_freq(inst.freq_x);
				signal_x_set_dir(inst.dir_x);
				signal_x_set_en(1);
				MOTOR_X_ACTIVE = 1;
				count_step_signal_x = 0;
			} else {
			}

			if (inst.num_steps_y > 0) {
				signal_y_set_freq(inst.freq_y);
				signal_y_set_dir(inst.dir_y);
				signal_y_set_en(1);
				MOTOR_Y_ACTIVE = 1;
				count_step_signal_y = 0;
			} else {
			}

			if (inst.num_steps_z > 0) {
				signal_z_set_freq(inst.freq_z);
				signal_z_set_dir(inst.dir_z);
				signal_z_set_en(1);
				MOTOR_Z_ACTIVE = 1;
				count_step_signal_z = 0;
			} else {
			}

			MACHINE_ACTIVE = 1; //TODO: Set this to 0 in timer interuption handlers


			//Update current_pos (FIXME: this should be done inside timer interuption handlers)
			CURRENT_POS.x = bro_code->point.x;
			CURRENT_POS.y = bro_code->point.y;
			CURRENT_POS.z = bro_code->point.z;

			//Free previously allocated memory for motor instruction to avoid memory leakage
			free(bro_code);
			free(ptr);
		}

		//for (int i = i; i < atoi(str[0]); i++)
		//        free(str[i]);
		//free(str[0]);
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
		SysTick_oppstart();
}
