#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorMotorB = motor(PORT2, ratio18_1, false);
motor_group leftMotor = motor_group(leftMotorMotorA, leftMotorMotorB);
motor rightMotorMotorA = motor(PORT3, ratio18_1, false);
motor rightMotorMotorB = motor(PORT4, ratio18_1, false);
motor_group rightMotor = motor_group(rightMotorMotorA, rightMotorMotorB);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}