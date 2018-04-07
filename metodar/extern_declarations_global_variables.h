// File: extern_declarations_global_variables.h				   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

#include "stdint.h"




//---------------------------------------
// Funksjonsprototyper
//---------------------------------------
extern void hardware_init(void);

extern void TIM2_init(void);
extern void TIM3_init(void);
extern void TIM4_init(void);
extern void TIM8_init(void);

extern void signal_x_set_freq(uint16_t freq);
extern void signal_x_set_dir(uint8_t dir);
extern void signal_x_set_en(uint8_t en);

extern void signal_y_set_freq(uint16_t freq);
extern void signal_y_set_dir(uint8_t dir);
extern void signal_y_set_en(uint8_t en);

extern void signal_z_set_freq(uint16_t freq);
extern void signal_z_set_dir(uint8_t dir);
extern void signal_z_set_en(uint8_t en);

extern void signal_drill_set_freq(uint16_t freq);
extern void signal_drill_set_dir(uint8_t dir);
extern void signal_drill_set_en(uint8_t en);

extern void GPIO_init(void);
extern void EXTI_init(void);
//---------------------------------------
// Globale variablar
//---------------------------------------

extern uint32_t counter_1ms;

extern volatile uint32_t count_step_signal_x;
extern volatile uint32_t count_step_signal_y;
extern volatile uint32_t count_step_signal_z;

extern volatile uint32_t number_of_steps_signal_x;
extern volatile uint32_t number_of_steps_signal_y;
extern volatile uint32_t number_of_steps_signal_z;

extern uint16_t PWM_period;
extern uint16_t PWM_width;
extern uint16_t PWM_prescale;



