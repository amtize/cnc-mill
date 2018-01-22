/* definitions.h defines variables and structs used in the program. */


struct Point {
	float x, y, z;
};

struct Bro_Code{
	Command cmd;
	int num_points;
	Point *points;
	int num_bezier;
	Point *bezier_points;
};

enum State {Movement, Slow, Rapid};

enum Command {Move_Linear, Move_Bezier, Calibrate, On, Off, Reset, SetState};
