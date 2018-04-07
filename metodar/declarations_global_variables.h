// File: declarations_global_variables.h					   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

//---------------------------------------
// Functional protocols
//---------------------------------------
void hardware_init(void);

void TIM2_init(void);
void TIM3_init(void);
void TIM4_init(void);
void TIM8_init(void);

void signal_x_set_freq(uint16_t freq);
void signal_x_set_dir(uint8_t dir);
void signal_x_set_en(uint8_t en);

void signal_y_set_freq(uint16_t freq);
void signal_y_set_dir(uint8_t dir);
void signal_y_set_en(uint8_t en);

void signal_z_set_freq(uint16_t freq);
void signal_z_set_dir(uint8_t dir);
void signal_z_set_en(uint8_t en);

void signal_drill_set_freq(uint16_t freq);
void signal_drill_set_dir(uint8_t dir);
void signal_drill_set_en(uint8_t en);

void GPIO_init(void);
void EXTI_init(void);
//---------------------------------------
// Globale variablar
//---------------------------------------
uint32_t counter_1ms;

volatile uint32_t count_step_signal_x = 0;
volatile uint32_t count_step_signal_y = 0;
volatile uint32_t count_step_signal_z = 0;

volatile uint32_t number_of_steps_signal_x = 0;
volatile uint32_t number_of_steps_signal_y = 0;
volatile uint32_t number_of_steps_signal_z = 0;

uint16_t PWM_period = 100;
uint16_t PWM_width = 50;
uint16_t PWM_prescale = 0;

//--------------------------------------------
// Datatypes
//--------------------------------------------

