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

//---------------------------------------
// Variables
//---------------------------------------

char* test_code = "L(1000,0,0);L(1000,1000,0);L(0,1000,0);L(0,0,0);";

//---------------------------------------
// Includes
//---------------------------------------

//---------------------------------------
// Methods
//---------------------------------------

Bro_Code * parse(char* str) {
    printf(str);

    Bro_Code *bro_code = malloc( sizeof (Bro_Code) );
    if (bro_code == NULL)
        return NULL;
    if (str == 'L') {
        //Linear Movement
        bro_code->cmd = Move_Linear;
        
    }
     for(;*str;str++) {
         switch (str) {
            case 'L': //Case Linear Movement command
                bro_code->cmd = Move_Linear;
                break;
            case '(': //Case Point Initiate
                bro_code->cmd = Move_Linear;
                break;
         }
     }
}

Point * parse_point(char* str) {

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
}
