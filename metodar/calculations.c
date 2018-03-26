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


//---------------------------------------
// Definitions
//---------------------------------------
//FIXME: This needs to be global
global int STEPS_PER_ROTATION = 200;        //200 steps per rotation
global int STEP_MULTIPLIER = 32;            //each step can be divided into 32 steps
global int DISTANCE_PER_ROTATION = 4000;    //micrometer
global float DISTANCE_PER_STEP = DISTANCE_PER_ROTATION / (STEP_MULTIPLIER * STEPS_PER_ROTATION); //Number of steps per micrometer
global float STEPS_PER_UM = 1 / DISTANCE_PER_STEP;

//IMPORTANT: UPDATE CURRENT_POS IN TIMER_INTERUPT_HANDLERS
global Point CURRENT_POS =  { .x = 0f, .y = 0f, .z = 0f };

global int MAX_X = 700000;                      //um
global int MAXY_Y = 500000;                     //um
global int MAX_FREQUENCY = 500;
global int MAX_FREQUENCY_ADJUSTED = MAX_FREQUENCY / 1.57079632679; //hz / (pi/2)
global int MAX_SPEED = DISTANCE_PER_STEP * MAX_FREQUENCY;

struct Motor_Instruction {
    int freq_x;
    int freq_y;
    int freq_z;
    Direction dir_x;
    Direction dir_y;
    Direction dir_z;
    int freq_drill;
    int num_steps;
};

struct Point {
	float x, y, z;
};

struct Bro_Code{
	Command cmd;
	//int num_points;
	//Point *points;
    Point point;
	//int num_bezier;
	//Point *bezier_points;
};

enum State {Movement, Slow, Rapid};

enum Command {Move_Linear, Move_Bezier, Calibrate, On, Off, Reset, SetState};


//---------------------------------------
// Local Variables
//---------------------------------------

//---------------------------------------
// Methods
//---------------------------------------

//calculate_frequencies recieves a Bro_code and returns a Motor_instruction.
//  a. The Motor_instruction struct contains frequencies and number of steps for all the motors in order to travel a certain distance.
//  TODO: documentate this more
//  !!TODO: instruction must be a pointer to avoid stack overflow!!
Motor_Instruction calculate_frequencies(Bro_code bro_code) {
    // Initialize a variable to modify and return at a later stage
    Motor_Instruction instruction = { 0, 0, 0, Forward, Forward, Forward, 0, 0};


    // Find relative movement vector by calculating difference in current_pos and desired_pos
    //  - Current pos is the point which the machine is currently at
    //  - Desired pos is the point specified in the recieved bro_code
    delta_x = CURRENT_POS.x - bro_code.point.x;
    delta_y = CURRENT_POS.y - bro_code.point.y;
    delta_z = CURRENT_POS.z - bro_code.point.z;


    // Set direction for motors and make all delta values positive if needed
    //  - Delta values are positive to make calculations easier at a later stage
    if (delta_x < 0) {
        instruction.dir_x = backward;
        delta_x = abs(delta_x);
    } // else not needed, standard direction is forward
    if (delta_y < 0) {
        instruction.dir_y = backward;
        delta_y = abs(delta_y);
    } // else not needed, standard direction is forward
    if (delta_z < 0) {
        instruction.dir_z = backward;
        delta_z = abs(delta_z);
    } // else not needed, standard direction is forward

    // Calculate frequencies:
    instruction.freq_x = MAX_FREQUENCY_ADJUSTED * atan2(delta_x, delta_y);
    instruction.freq_y = MAX_FREQUENCY_ADJUSTED * atan2(delta_y, delta_x);
    instruction.freq_z = 0;
    // Freq_z currently set to 0, fix this. 

    // Calculate number of steps
    len = sqrt( pow(delta_x, 2) + pow(delta_y, 2) );
    instruction.num_steps = len * STEPS_PER_UM;

    return instruction;
}
