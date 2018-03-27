// File: calculations.c
// BSc CNC Mill
// Ove Nicolai Dalheim, Tarjei Gr�sdal
//---------------------------------------

//---------------------------------------
// Includes
//---------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <c:\cygwin64\home\Tarjei\cnc-mill\metodar\calculations.h>


//---------------------------------------
// Definitions
//---------------------------------------
//FIXME: This needs to be global
#define STEPS_PER_ROTATION 200        //200 steps per rotation
#define STEP_MULTIPLIER 32            //each step can be divided into 32 steps
#define DISTANCE_PER_ROTATION 4000    //micrometer
static float DISTANCE_PER_STEP = (float)DISTANCE_PER_ROTATION / (STEP_MULTIPLIER * STEPS_PER_ROTATION); //Number of steps per micrometer
//static int STEPS_PER_UM = 1 /DISTANCE_PER_STEP;

static int MAX_X =700000;                      //um
static int MAXY_Y =500000;                     //um
#define MAX_FREQUENCY 800
static float MAX_FREQUENCY_ADJUSTED = MAX_FREQUENCY / 1.57079632679; //hz / (pi/2)
static float MAX_SPEED = 0;//DISTANCE_PER_STEP * MAX_FREQUENCY;

enum State { Movement, Slow, Rapid };

enum Command { Move_Linear, Move_Bezier, Calibrate, On, Off, Reset, SetState };

enum Direction { forward, backward };

typedef struct Motor_Instruction {
    int freq_x;
    int freq_y;
    int freq_z;
    enum Direction dir_x;
    enum Direction dir_y;
    enum Direction dir_z;
    int freq_drill;
    int num_steps;
} Motor_Instruction;

typedef struct Point {
	float x, y, z;
} Point;

typedef struct Bro_Code {
	enum Command cmd;
	//int num_points;
	//Point *points;
    struct Point point;
	//int num_bezier;
	//Point *bezier_points;
} Bro_Code;

//---------------------------------------
// Local Variables
//---------------------------------------

//IMPORTANT: UPDATE CURRENT_POS IN TIMER_INTERUPT_HANDLERS
Point CURRENT_POS =  { .x = 0, .y = 0, .z = 0 };

//---------------------------------------
// Function Declarations
//---------------------------------------

static Motor_Instruction * calculate_frequencies(Bro_Code* bro_code); 


//---------------------------------------
// Methods
//---------------------------------------
int main(void) {
    Point pt = { 10000.0, 250000, 0 };
    Bro_Code bc = { Move_Linear, pt };
    Motor_Instruction inst;
    Motor_Instruction *ptr = calculate_frequencies(&bc);
    inst = *ptr;

    printf("frequency x:%d\n", inst.freq_x);
    printf("frequency y:%d\n", inst.freq_y);
    printf("number of steps:%d", inst.num_steps);

    return 0;
}


//calculate_frequencies recieves a Bro_code and returns a Motor_instruction.
//  a. The Motor_instruction struct contains frequencies and number of steps for all the motors in order to travel a certain distance.
//  TODO: documentate this more
//  !!TODO: instruction must be a pointer to avoid stack overflow!!
Motor_Instruction * calculate_frequencies(Bro_Code* bro_code) {
    // Initialize a variable to modify and return at a later stage
    //Motor_Instruction instruction = { 0, 0, 0, forward, forward, forward, 0, 0};

    Motor_Instruction *inst = malloc (sizeof (Motor_Instruction));
    if (inst == NULL)
        return NULL;

    // Find relative movement vector by calculating difference in current_pos and desired_pos
    //  - Current pos is the point which the machine is currently at
    //  - Desired pos is the point specified in the recieved bro_code
    float delta_x = CURRENT_POS.x - bro_code->point.x;
    float delta_y = CURRENT_POS.y - bro_code->point.y;
    float delta_z = CURRENT_POS.z - bro_code->point.z;

    // Set direction for motors and make all delta values positive if needed
    //  - Delta values are positive to make calculations easier at a later stage
    if (delta_x < 0) {
        //instruction.dir_x = backward;
        inst->dir_x = backward;
        delta_x = abs(delta_x);
    } else {
        inst->dir_x = forward;
    }
    if (delta_y < 0) {
        //instruction.dir_y = backward;
        inst->dir_y = backward;
        delta_y = abs(delta_y);
    } else {
        inst->dir_y = forward;
    }
    if (delta_z < 0) {
        //instruction.dir_z = backward;
        inst->dir_z = backward;
        delta_z = abs(delta_z);
    } else {
        inst->dir_z = forward;
    }

    // Calculate frequencies:
    inst->freq_x = MAX_FREQUENCY_ADJUSTED * atan2(delta_x, delta_y);
    inst->freq_y = MAX_FREQUENCY_ADJUSTED * atan2(delta_y, delta_x);
    inst->freq_z = 0;
    // TODO: Freq_z currently set to 0, fix this. 

    // Calculate number of steps
    float len = sqrt( pow(delta_x, 2) + pow(delta_y, 2) );
    inst->num_steps = (int) len / DISTANCE_PER_STEP; //* (1 / DISTANCE_PER_STEP);

    printf("Length of vector:%.6f\n", (float)len);

    return inst;
}
