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
#include <string.h>

//---------------------------------------
// Variables
//---------------------------------------

char* test_code = "L(1000,0,0);L(1000,1000,0);L(0,1000,0);L(0,0,0);";

//---------------------------------------
// Includes
//---------------------------------------
Point * parse_point(char *str);
void strcat_c (char *str, char c);

Motor_Instruction * calculate_frequencies(Bro_Code* bro_code);
Point CURRENT_POS =  { .x = 0, .y = 0, .z = 0 };
//---------------------------------------
// Methods
//---------------------------------------

Bro_Code * parse(char *str) {
    Bro_Code *bro_code = malloc( sizeof (Bro_Code) );
    if (bro_code == NULL)
        return NULL;

     for(;*str;str++) {
         if (*str == 'L') {
            bro_code->cmd = Move_Linear;
            str++; //Jumping over "L"
            bro_code->point = *parse_point(str);
            break;
        }
    }
    return bro_code;
}

Point * parse_point(char *str) {
    Point *point = malloc( sizeof (Point) ); //TODO: Free this

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

int main(void) {
    Bro_Code *bro_codes[128];
    int i = 0;
    char temp[128];
    int temp_i = 0;
    for(;*test_code;test_code++) {
        //putchar(*test_code);
        if (*test_code == ';') {
            bro_codes[i] = parse(temp);

            //Clear temp string
            temp[0] = '\0';
            
            i++;
        } else {
            //TODO: more efficient string concat
            strcat_c(temp, *test_code);
        }
    }
    int y = 0;
    for (y; y < 4; y++) {
        Motor_Instruction *ptr = calculate_frequencies(bro_codes[y]);
        Motor_Instruction inst = *ptr;
        printf("frequency x:%d\n", inst.freq_x);
        printf("frequency y:%d\n", inst.freq_y);
        printf("number of steps:%d\n", inst.num_steps);
        printf("direction x:%d direction y:%d\n\n", inst.dir_x, inst.dir_y);

        CURRENT_POS.x = bro_codes[y]->point.x;
        CURRENT_POS.y = bro_codes[y]->point.y;
        CURRENT_POS.z = bro_codes[y]->point.z;

        //Free previously allocated memory for motor instruction to avoid memory leakage
        free(ptr);
    }
    return 0;
}





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
