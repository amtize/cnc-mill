// File: calculations.c
// BSc CNC Mill
// Ove Nicolai Dalheim, Tarjei Gr�sdal
//---------------------------------------

//---------------------------------------
// Includes
//---------------------------------------

#include "stm32f30x.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <extern_declarations_global_variables.h>

//---------------------------------------
// Variables
//---------------------------------------
#define STEPS_PER_ROTATION 200        //200 steps per rotation
#define STEP_MULTIPLIER 32            //each step can be divided into 32 steps
#define DISTANCE_PER_ROTATION 4000    //micrometer
float DISTANCE_PER_STEP = (float)DISTANCE_PER_ROTATION / (STEP_MULTIPLIER * STEPS_PER_ROTATION); //Number of steps per micrometer
//static int STEPS_PER_UM = 1 /DISTANCE_PER_STEP;

//static int MAX_X =700000;                      //um
//static int MAXY_Y =500000;                     //um
#define MAX_FREQUENCY 800
float MAX_FREQUENCY_ADJUSTED = MAX_FREQUENCY / 1.57079632679; //hz / (pi/2)
//static float MAX_SPEED = 0;//DISTANCE_PER_STEP * MAX_FREQUENCY;







enum STATE { Movement, Slow, Rapid } STATE;

enum COMMAND { Move_Linear, Move_Bezier, Calibrate, On, Off, Reset, SetState } COMMAND;

typedef struct MOTOR_INSTRUCTION {
    uint32_t            freq_x, freq_y, freq_z, freq_drill;
    enum DIRECTION  	dir_x,  dir_y,  dir_z;
    uint32_t            num_steps_x, num_steps_y, num_steps_z;
} MOTOR_INSTRUCTION;

typedef struct BRO_CODE {
	enum COMMAND cmd;
	//int num_points;
	//Point *points;
    struct POINT point;
	//int num_bezier;
	//Point *bezier_points;
} BRO_CODE;

//---------------------------------------
// Includes
//---------------------------------------
POINT * parse_point(char *str);
void strcat_c (char *str, char c);
//Bro_Code * parse(char *str);
//char ** split(char *str, char c);
//Motor_Instruction * calculate_frequencies(Bro_Code* bro_code);
//---------------------------------------
// Methods
//---------------------------------------

BRO_CODE * parse(char *str) {
    BRO_CODE *bro_code = malloc( sizeof (BRO_CODE) );
    if (bro_code == NULL)
        return NULL;

     for(;*str;str++) {
         if (*str == 'L') {
            bro_code->cmd = Move_Linear;
            str++; //Increment str to "jump over" 'L'
            POINT *point = parse_point(str);
            bro_code->point = *point;
            free(point);
            break;
        }
    }
    return bro_code;
}

POINT * parse_point(char *str) {
    POINT *point = malloc( sizeof (POINT) );

    char x[16], y[16], z[16];

    //Clear strings (this is needed because there may be old values stored in the arrays)
    x[0] = '\0';
    y[0] = '\0';
    z[0] = '\0';

    char* temp=str;

    for (; *temp; ++temp){
        if (*temp == '(') continue;
        if (*temp == ',') break;
        strcat_c(x, *temp);
    }
    temp++; //Increment temp to "jump over" ','
    for (; *temp; ++temp){
        if (*temp == ',') break;
        strcat_c(y, *temp);
    }
    temp++; //Increment temp to "jump over" ','
    for (; *temp; ++temp){
        if (*temp == ')') break;
        strcat_c(z, *temp);
    }

    //Convert from string to floats
    point->x = atof(x);
    point->y = atof(y);
    point->z = atof(z);

    return point;
}

//Concat a char onto a string
void strcat_c (char *str, char c) {
    for (;*str;str++); // note the terminating semicolon here.
    *str++ = c;
    *str++ = 0;
}

// split() splits a string str on character c, and returns an array of strings
//    ! - the first index of the returned array is the length of the array
char ** split(char *str, char c) {
    int ARR_LENGTH = 64;
    char **arr;
    arr = malloc(ARR_LENGTH * sizeof(char*));
    for (int i = 0; i < ARR_LENGTH; i++)
        arr[i] = malloc((ARR_LENGTH+1) * sizeof(char));

    char temp[128];

    int i = 1; //Reserve first spot in array for length of array

    for(;*str;str++) {
        if (i >= ARR_LENGTH) { //Array is full, reallocate more memory
            printf("Array out of memory, reallocating. Old length: %d, new length: %d\n", ARR_LENGTH, (ARR_LENGTH * 2));
            ARR_LENGTH = ARR_LENGTH * 2;
            arr = (char **) realloc(arr, ARR_LENGTH * sizeof(char*));
            for (int i_ = i; i_ < ARR_LENGTH; i_++)
                arr[i_] = malloc((ARR_LENGTH+1) * sizeof(char));
        }
        if (*str == c) {
            strcpy(arr[i], temp);
            //Clear temp string
            temp[0] = '\0';
            i++;
        } else {
            //TODO: more efficient string concat, doesn't have to loop through each time
            strcat_c(temp, *str);
        }
    }

    char i_c[12]; //Convert counter i to char
    snprintf(i_c, 12, "%d", i - 1);

    strcpy(arr[0], i_c);

    return arr;
}

//int main(void) {
//    Bro_Code *bro_codes[128];
//
//    char **str;
//    str = split(test_code, ';');
//
//    printf("Number of bro codes: ");
//    printf(str[0]);
//    printf("\n\n");
//
//    int y = 1;
//    for (y; y <= atoi(str[0]); y++) { //str[0] is reserved for length of array
//        Bro_Code *bro_code = parse(str[y]);
//        Motor_Instruction *ptr = calculate_frequencies(bro_code);
//        Motor_Instruction inst = *ptr;
//        printf("frequency x:%d\n", inst.freq_x);
//        printf("frequency y:%d\n", inst.freq_y);
//        printf("number of steps:%d\n", inst.num_steps);
//        printf("direction x:%d direction y:%d\n\n", inst.dir_x, inst.dir_y);
//
//        CURRENT_POS.x = bro_code->point.x;
//        CURRENT_POS.y = bro_code->point.y;
//        CURRENT_POS.z = bro_code->point.z;
//
//        //Free previously allocated memory for motor instruction to avoid memory leakage
//        free(bro_code);
//        free(ptr);
//    }
//
//    free(str);
//    return 0;
//}





MOTOR_INSTRUCTION * calculate_frequencies(BRO_CODE* bro_code) {

    //Allocate memory for motor instruction. Free() must be called at a later stage
	MOTOR_INSTRUCTION *inst = malloc ( sizeof(MOTOR_INSTRUCTION) );
    if (inst == NULL) //Out of memory
        return NULL;

    // Find relative movement vector by calculating difference in current_pos and desired_pos
    //  - Current pos is the point which the machine is currently at
    //  - Desired pos is the point specified in the recieved bro_code
    float delta_x = CURRENT_POS.x - bro_code->point.x;
    float delta_y = CURRENT_POS.y - bro_code->point.y;
    float delta_z = CURRENT_POS.z - bro_code->point.z;

    // Set direction for motors and make all delta values positive if needed
    //  - Delta values are set positive to make calculations easier at a later stage
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
    inst->num_steps_x = (uint32_t) delta_x / DISTANCE_PER_STEP;
    inst->num_steps_y = (uint32_t) delta_y / DISTANCE_PER_STEP;
    inst->num_steps_z = (uint32_t) delta_z / DISTANCE_PER_STEP;

    return inst;
}
