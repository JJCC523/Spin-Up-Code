using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern signature Vision8__REDHIGH;
extern signature Vision8__BLUEHIGH;
extern signature Vision8__SIG_3;
extern signature Vision8__SIG_4;
extern signature Vision8__SIG_5;
extern signature Vision8__SIG_6;
extern signature Vision8__SIG_7;
extern vision Vision8;
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
extern motor flywheel;
extern digital_out Endgame;
extern motor roller;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );