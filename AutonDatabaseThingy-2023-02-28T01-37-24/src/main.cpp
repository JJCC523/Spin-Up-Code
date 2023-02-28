/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\jack0                                            */
/*    Created:      Mon Feb 27 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

competition Competition;

float X = getGlobalX();
float Y = getGlobalY();



int backgroundTasks()
{
  while (true)
  {
    updatePosition(); // Update the odometry position
    // Draw the debug values and the field dashboard
    //values();
    //odomDisplay();
    //graph();
    task::sleep(10); // Wait some time between odometry cycles. Test making it shorter for better position estimates
  }
  return 0;
}

using namespace vex;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Indexer = 0;
  Endgame = 0;
  Endgame2 = 0;
  Wall = 0;
  Inertial5.calibrate();
  wait(3,seconds);
  while(true){

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  }
}

 

void autonomous(void) {
  setStartingPos(0, 0);
  thread o(backgroundTasks);
  
  
}

  
int rishiethefishielovesjews = 0;
int shooter = 0;

int rishithefishilovesandhatesjews(){
  /*if(Controller1.ButtonL2.pressing()){
    if(p == 2){
    getDegToPoint(-70.9 , -0.7);
    setTarget(-70.9 , -0.7);
    turnToTarget(100);
    while(!Vision8.getSignature(PORT8, Vision8__REDHIGH)){
      
    fL.spin(forward, 100 , percent);
    bL.spin(forward, 100, percent);
    fR.spin(reverse, 100, percent);
    bR.spin(reverse, 100, percent);
    }
    fL.stop();
    fR.stop();
    bL.stop();
    bR.stop();
    fL.setStopping(hold);
    fR.setStopping(hold);
    bL.setStopping(hold);
    bR.setStopping(hold);
    }
    if(p == 1){
    getDegToPoint(-86.3 , 1);
    setTarget(-86 , 1);
    turnToTarget(100);
    }
  }*/
  return(1);
}
int test()
{
  while (getTotalDistance() < 10)
  {
    task::sleep(10);
  } 
  Brain.Screen.setFillColor(color(200, 80, 30)); // green in rgb
  Brain.Screen.setPenWidth(0);
  Brain.Screen.drawRectangle(0, 0, 480, 272); // fill entire screen

  return 0;
}

int rightendgame = 0;
int leftendgame = 0;
int endgame_safe = 0;
int wallEndgame = 0;

void usercontrol(void) {

  while (1) {
    // Deadband stops the motors when Axis values are close to zero.
  //int deadband = 5;
  
  while (true) {
    thread a(backgroundTasks);
    //thread k(detectDisc);
    fL.setStopping(hold); 
    fR.setStopping(hold);
    bR.setStopping(hold);
    bL.setStopping(hold);

    int forwardcontroller = Controller1.Axis3.position(percent);
    int sidewayscontroller= Controller1.Axis4.position(percent);
    int turncontroller= Controller1.Axis1.position(percent);

  fR.spin(forward, forwardcontroller-sidewayscontroller-turncontroller, percent);
  fL.spin(forward, forwardcontroller+sidewayscontroller+turncontroller, percent);
  bR.spin(forward, forwardcontroller+sidewayscontroller-turncontroller, percent);
  bL.spin(forward, forwardcontroller-sidewayscontroller+turncontroller, percent);

  if(Controller1.ButtonR2.pressing()){
    while(Controller1.ButtonR2.pressing()){
      wait(10,msec);
    }
    Brain.Screen.print("Pos: (%.1f, %.1f)     ", X, Y);
    Brain.Screen.newLine(); 
  }
    wait(20, msec);  
  }
}
}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec); 
  }
}