using namespace vex;

extern brain Brain;

// VEXcode devices
extern inertial Inertial1;
extern rotation Xrot;
extern rotation Yrot;
extern motor fl;
extern motor bl;
extern motor fr;
extern motor br;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );