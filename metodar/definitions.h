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
    int             freq_x, freq_y, freq_z;
    enum Direction  dir_x,  dir_y,  dir_z;
    int             freq_drill, num_steps;
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