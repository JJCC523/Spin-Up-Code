#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision8__REDHIGH = signature (1, 3963, 8929, 6446, -1339, -255, -797, 0.7, 0);
signature Vision8__BLUEHIGH = signature (2, -1917, 1, -958, 1737, 7149, 4443, 0.9, 0);
vision Vision8 = vision (PORT8, 50, Vision8__REDHIGH, Vision8__BLUEHIGH);
triport Expander11 = triport(PORT11); 
encoder RightSide = encoder(Brain.ThreeWirePort.A);
encoder LeftSide = encoder(Brain.ThreeWirePort.C);
encoder BackSide = encoder(Brain.ThreeWirePort.E);
//distance DiscSensor = distance(PORT12);
motor fL = motor(PORT2, ratio18_1, true);
digital_out Indexer = digital_out(Brain.ThreeWirePort.G);
motor bL = motor(PORT9, ratio6_1, true);
motor fR = motor(PORT1, ratio6_1, false);
motor bR = motor(PORT10, ratio6_1, false);
inertial Inertial5 = inertial(PORT5);
controller Controller1 = controller(primary);
motor IntakeMotorA = motor(PORT13, ratio6_1, true);
motor IntakeMotorB = motor(PORT15, ratio6_1, false);
motor_group Intake = motor_group(IntakeMotorA, IntakeMotorB);
optical Optical4 = optical(PORT4);
motor flywheelMotorA = motor(PORT6, ratio6_1, false);
motor flywheelMotorB = motor(PORT7, ratio6_1, false);
motor_group flywheel = motor_group(flywheelMotorA, flywheelMotorB);
digital_out Endgame = digital_out(Brain.ThreeWirePort.H);

/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}