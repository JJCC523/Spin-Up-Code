#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor fL = motor(PORT1, ratio6_1, true);
motor bL = motor(PORT2, ratio6_1, true);
motor fR = motor(PORT10, ratio6_1, false);
motor bR = motor(PORT9, ratio6_1, false);
inertial Inertial5 = inertial(PORT5);
motor RollerWheel = motor(PORT7, ratio18_1, false);
/*vex-vision-config:begin*/
vision Vision6 = vision (PORT6, 50);
/*vex-vision-config:end*/
encoder RightSide = encoder(Brain.ThreeWirePort.A);
encoder LeftSide = encoder(Brain.ThreeWirePort.C);
encoder BackSide = encoder(Brain.ThreeWirePort.E);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1UpDownButtonsControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonUp/ButtonDown status to control fL
      if (Controller1.ButtonUp.pressing()) {
        fL.spin(forward);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonDown.pressing()) {
        fL.spin(reverse);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (!Controller1UpDownButtonsControlMotorsStopped) {
        fL.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1UpDownButtonsControlMotorsStopped = true;
      }
      // check the ButtonX/ButtonB status to control fR
      if (Controller1.ButtonX.pressing()) {
        fR.spin(forward);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonB.pressing()) {
        fR.spin(reverse);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (!Controller1XBButtonsControlMotorsStopped) {
        fR.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1XBButtonsControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}