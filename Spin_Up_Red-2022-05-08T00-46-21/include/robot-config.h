using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor fL;
extern motor bL;
extern motor fR;
extern motor bR;
extern inertial Inertial5;
extern motor RollerWheel;
extern signature Vision6__RED_ROLLER;
extern signature Vision6__BLUE_ROLLER;
extern signature Vision6__SIG_3;
extern signature Vision6__SIG_4;
extern signature Vision6__SIG_5;
extern signature Vision6__SIG_6;
extern signature Vision6__SIG_7;
extern vision Vision6;
extern rotation Rotation8;
extern rotation Rotation9;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );