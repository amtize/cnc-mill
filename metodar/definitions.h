//enum State { Movement, Slow, Rapid };
//
//enum Command { Move_Linear, Move_Bezier, Calibrate, On, Off, Reset, SetState };
//
//enum Direction { forward, backward };
//
//typedef struct Motor_Instruction {
//    int             freq_x, freq_y, freq_z;
//    enum Direction  dir_x,  dir_y,  dir_z;
//    int             freq_drill, num_steps;
//} Motor_Instruction;
//
//typedef struct Point {
//	float x, y, z;
//} Point;
//
//typedef struct Bro_Code {
//	enum Command cmd;
//	//int num_points;
//	//Point *points;
//    struct Point point;
//	//int num_bezier;
//	//Point *bezier_points;
//} Bro_Code;
