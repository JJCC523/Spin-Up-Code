using namespace vex;

extern brain Brain;

// VEXcode devices
extern triport Expander11;
extern encoder RightSide;
extern encoder LeftSide;
extern encoder BackSide;
//extern distance DiscSensor;
extern motor fL;
extern motor fL;
extern motor bL;
extern motor fR;
extern motor bR;
extern inertial Inertial5;
extern encoder RightSide;
extern encoder LeftSide;
extern encoder BackSide;
extern controller Controller1;
extern motor_group Intake;
extern digital_out Indexer;
extern optical Optical4;
extern motor_group flywheel;
extern digital_out Endgame;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );