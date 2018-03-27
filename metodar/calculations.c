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
//FIXME: Fix this path
#include <C:\cygwin64\home\mikrolab\cnc-mill\metodar\definitions.h>
//#include <c:\cygwin64\home\Tarjei\cnc-mill\metodar\calculations.h>


//---------------------------------------
// Definitions
//---------------------------------------
//FIXME: This needs to be global


//---------------------------------------
// Local Variables
//---------------------------------------

//IMPORTANT: UPDATE CURRENT_POS IN TIMER_INTERUPT_HANDLERS
Point CURRENT_POS =  { .x = 0, .y = 0, .z = 0 };

//---------------------------------------
//        Function Declarations
//---------------------------------------

static Motor_Instruction * calculate_frequencies(Bro_Code* bro_code); 


//---------------------------------------
//              Methods
//---------------------------------------
int main(void) {
    Point pt = { -10000.0, 250000, 0 };
    Bro_Code bc = { Move_Linear, pt };
    //Motor_Instruction inst = *calculate_frequencies(&bc);
    Motor_Instruction *ptr = calculate_frequencies(&bc);
    Motor_Instruction inst = *ptr;

    printf("frequency x:%d\n", inst.freq_x);
    printf("frequency y:%d\n", inst.freq_y);
    printf("number of steps:%d\n", inst.num_steps);
    printf("direction x:%d direction y:%d\n", inst.dir_x, inst.dir_y);

    //Free previously allocated memory for motor instruction to avoid memory leakage
    free(ptr);
    return 0;
}


//calculate_frequencies recieves a Bro_code and returns a Motor_instruction.
//  a. The Motor_instruction struct contains frequencies and number of steps for all the motors in order to travel a certain distance.
//  TODO: documentate this more
Motor_Instruction * calculate_frequencies(Bro_Code* bro_code) {

    //Allocate memory for motor instruction. Free() must be called at a later stage
    Motor_Instruction *inst = malloc ( sizeof(Motor_Instruction) );
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
    if (delta_x > 0) {
        inst->dir_x = backward;
    } else {
        inst->dir_x = forward;
        delta_x = abs(delta_x);
    }
    if (delta_y > 0) {
        inst->dir_y = backward;
    } else {
        inst->dir_y = forward;
        delta_y = abs(delta_y);
    }
    if (delta_z > 0) {
        inst->dir_z = backward;
    } else {
        inst->dir_z = forward;
        delta_z = abs(delta_z);
    }

    // Calculate frequencies:
    inst->freq_x = MAX_FREQUENCY_ADJUSTED * atan2(delta_x, delta_y);
    inst->freq_y = MAX_FREQUENCY_ADJUSTED * atan2(delta_y, delta_x);
    inst->freq_z = 0;
    // TODO: Freq_z currently set to 0, fix this. 

    // Calculate number of steps
    float len = sqrt( pow(delta_x, 2) + pow(delta_y, 2) );
    inst->num_steps = (int) len / DISTANCE_PER_STEP;

    printf("length of vector:%.6f\n", (float)len);

    return inst;
}
