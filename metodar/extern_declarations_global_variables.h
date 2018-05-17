// File: extern_declarations_global_variables.h				   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

#include "stdint.h"


//---------------------------------------
// Datatypes
//---------------------------------------

typedef struct POINT {
	int32_t x, y, z;
} POINT;

enum DIRECTION { forward, backward } DIRECTION;

//---------------------------------------
// Funksjonsprototyper
//---------------------------------------
extern void hardware_init(void);

extern void TIM2_init(void);
extern void TIM3_init(void);
extern void TIM4_init(void);
extern void TIM8_init(void);

extern void SysTick_oppstart(void);

extern void signal_x_set_freq(uint16_t freq);
extern void signal_x_set_dir(enum DIRECTION dir);
extern void signal_x_set_en(uint8_t en);

extern void signal_y_set_freq(uint16_t freq);
extern void signal_y_set_dir(enum DIRECTION dir);
extern void signal_y_set_en(uint8_t en);

extern void signal_z_set_freq(uint16_t freq);
extern void signal_z_set_dir(enum DIRECTION dir);
extern void signal_z_set_en(uint8_t en);

extern void signal_drill_set_freq(uint16_t freq);
extern void signal_drill_set_dir(enum DIRECTION dir);
extern void signal_drill_set_en(uint8_t en);

extern void GPIO_init(void);
extern void EXTI_init(void);
extern void USART2_oppstart(void);


extern void usart_send_line(const char *s);
extern void usart_send_newline(void);
extern void usart_send_string(const char *s);
extern void usart_send(const char chr);

//extern BRO_CODE * parse(char *str);
//extern char ** split(char *str, char c);
//extern MOTOR_INSTRUCTION * calculate_frequencies(BRO_CODE* bro_code);
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

extern volatile uint16_t MACHINE_ACTIVE;
extern volatile uint16_t MOTOR_X_ACTIVE;
extern volatile uint16_t MOTOR_Y_ACTIVE;
extern volatile uint16_t MOTOR_Z_ACTIVE;

extern volatile uint16_t MACHINE_STATE;

extern volatile uint16_t END_STOP_ENGAGED;

extern volatile uint16_t EOAX;
extern volatile uint16_t SOAX;
extern volatile uint16_t EOAY;
extern volatile uint16_t SOAY;

extern POINT CURRENT_POS;

extern volatile uint16_t BRO_CODE_BUFFERED;
extern char *test_code;
