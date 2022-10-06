using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor fL;
extern motor bL;
extern motor fR;
extern motor bR;
extern inertial Inertial5;
extern motor RollerWheel;
extern encoder RightSide;
extern encoder LeftSide;
extern encoder BackSide;
extern controller Controller1;
extern motor Intake;
extern optical Optical6;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );