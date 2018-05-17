// File: declarations_global_variables.h					   //
// BSc CNC Mill												   //
// Ove Nicolai Dalheim, Tarjei Græsdal						   //
//-------------------------------------------------------------//

//--------------------------------------------
// Datatypes
//--------------------------------------------

enum STATE { Movement, Slow, Rapid } STATE;

enum COMMAND { Move_Linear, Move_Bezier, Calibrate, On, Off, Reset, SetState } COMMAND;

enum DIRECTION { forward, backward } DIRECTION;

typedef struct MOTOR_INSTRUCTION {
    uint32_t            freq_x, freq_y, freq_z, freq_drill;
    enum DIRECTION  	dir_x,  dir_y,  dir_z;
    uint32_t            num_steps_x, num_steps_y, num_steps_z;
} MOTOR_INSTRUCTION;

typedef struct POINT {
	int32_t x, y, z;
} POINT;

typedef struct BRO_CODE {
	enum COMMAND cmd;
	//int num_points;
	//Point *points;
    struct POINT point;
	//int num_bezier;
	//Point *bezier_points;
} BRO_CODE;

//---------------------------------------
// Functional protocols
//---------------------------------------
void hardware_init(void);

void TIM2_init(void);
void TIM3_init(void);
void TIM4_init(void);
void TIM8_init(void);

void SysTick_oppstart(void);

void signal_x_set_freq(uint16_t freq);
void signal_x_set_dir(enum DIRECTION dir);
void signal_x_set_en(uint8_t en);

void signal_y_set_freq(uint16_t freq);
void signal_y_set_dir(enum DIRECTION dir);
void signal_y_set_en(uint8_t en);

void signal_z_set_freq(uint16_t freq);
void signal_z_set_dir(uint8_t dir);
void signal_z_set_en(uint8_t en);

void signal_drill_set_freq(uint16_t freq);
void signal_drill_set_dir(enum DIRECTION dir);
void signal_drill_set_en(uint8_t en);

void GPIO_init(void);
void EXTI_init(void);
void USART2_oppstart(void);

void usart_send_line(const char *s);
void usart_send_newline(void);
void usart_send_string(const char *s);
void usart_send(const char chr);


void handle_end_stop(void);
BRO_CODE * parse(char *str);
char ** split(char *str, char c);
MOTOR_INSTRUCTION * calculate_frequencies(BRO_CODE* bro_code);
//---------------------------------------
// Globale variablar
//---------------------------------------
uint32_t counter_1ms = 0;

volatile uint32_t count_step_signal_x = 0;
volatile uint32_t count_step_signal_y = 0;
volatile uint32_t count_step_signal_z = 0;

volatile uint32_t number_of_steps_signal_x = 0;
volatile uint32_t number_of_steps_signal_y = 0;
volatile uint32_t number_of_steps_signal_z = 0;

uint16_t PWM_period = 100;
uint16_t PWM_width = 50;
uint16_t PWM_prescale = 0;

volatile uint16_t MACHINE_ACTIVE = 1;
volatile uint16_t MOTOR_X_ACTIVE = 0;
volatile uint16_t MOTOR_Y_ACTIVE = 0;
volatile uint16_t MOTOR_Z_ACTIVE = 0;

volatile uint16_t END_STOP_ENGAGED = 0;

volatile uint16_t EOAX = 0;
volatile uint16_t SOAX = 0;
volatile uint16_t EOAY = 0;
volatile uint16_t SOAY = 0;

volatile uint16_t MACHINE_STATE = 0;

volatile POINT CURRENT_POS = { .x = 0, .y = 0, .z = 0 };

volatile uint16_t BRO_CODE_BUFFERED = 0;

char *test_code;
