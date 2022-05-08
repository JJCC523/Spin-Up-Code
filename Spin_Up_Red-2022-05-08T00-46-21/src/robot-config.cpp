#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor fL = motor(PORT1, ratio18_1, false);
motor bL = motor(PORT2, ratio18_1, false);
motor fR = motor(PORT3, ratio18_1, false);
motor bR = motor(PORT4, ratio18_1, false);
inertial Inertial5 = inertial(PORT5);
motor RollerWheel = motor(PORT7, ratio18_1, false);
/*vex-vision-config:begin*/
vision Vision6 = vision (PORT6, 50);
/*vex-vision-config:end*/
rotation Rotation8 = rotation(PORT8, false);
rotation Rotation9 = rotation(PORT9, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}