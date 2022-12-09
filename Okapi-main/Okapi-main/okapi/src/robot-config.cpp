#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
inertial Inertial1 = inertial(PORT1);
rotation Xrot = rotation(PORT11, false);
rotation Yrot = rotation(PORT9, false);
motor fl = motor(PORT4, ratio18_1, false);
motor bl = motor(PORT5, ratio18_1, false);
motor fr = motor(PORT19, ratio18_1, true);
motor br = motor(PORT21, ratio18_1, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}