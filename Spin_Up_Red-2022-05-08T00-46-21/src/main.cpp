/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// fL                   motor         1               
// bL                   motor         2               
// fR                   motor         3               
// bR                   motor         4               
// Inertial5            inertial      5               
// RollerWheel          motor         7               
// Vision6              vision        6               
// Rotation8            rotation      8               
// Rotation9            rotation      9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here



//settings
double kP = 0.0;
double kI = 0.0;
double kD = 0.0;

double turnkP = 0.0;
double turnkI = 0.0;
double turnkD = 0.0;

int desiredValue = 200;
int desiredTurnValue = 0;

int error; //Sensor Value - Target Value : position
int prevError = 0; //position 20 msecs ago
int derivative; //error-prevError : speed
int totalError = 0; //TotalError= totalError + error

int turnError; //Sensor Value - Target Value : position
int turnPrevError = 0; //position 20 msecs ago
int turnDerivative; //error-prevError : speed
int turnTotalError = 0; //TotalError= totalError + error

bool enableDrivePID= true;

bool resetDriveSensors=false;

int drivePID(){
  while(enableDrivePID){
    if(resetDriveSensors){
      resetDriveSensors = false;

      Rotation8.setPosition(0, degrees);
      Rotation9.setPosition(0, degrees);

    }

    //int GyroPosition = Inertial5.heading(degrees);
    //wheel position
    int LeftWheelPosition = Rotation8.position(degrees);
    int RightWheelPosition = Rotation8.position(degrees);


///////////////////////////////////////////////////////////////////////////
//Lateral movement PID
//////////////////////////////////////////////////////////////////////////

    //average of the rotation
    int averagePosition = (LeftWheelPosition+RightWheelPosition)/2;

    //potential
    error = averagePosition - desiredValue;

    //derivative
    derivative = error - prevError;

    //velocity > position > absement(position*time)
    totalError += error;

    double lateralMotorPower = (error * kP + derivative * kD); //+ totalError * kI); Doesnt work well


///////////////////////////////////////////////////////////////////////////
//Turning movement PID
//////////////////////////////////////////////////////////////////////////

//average of the rotation
    int turnDifference = (LeftWheelPosition - RightWheelPosition);

    //potential
    turnError = turnDifference - desiredTurnValue;

    //derivative
    turnDerivative = turnError - turnPrevError;

    //velocity > position > absement(position*time)
    turnTotalError += error;

    double turnMotorPower = (turnError * turnkP + turnDerivative * turnkD); //+ turnTotalError * turnkI); Doesnt work well


/////////////////////////////////////////////////////////////////////////

    fL.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    fR.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);
    bL.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    bR.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);


    prevError = error;
    turnPrevError = turnError;
    vex::task::sleep(20);
  }

  return 1;
}

void rollerMech(){
  while(!Vision6.takeSnapshot(Vision6__RED_ROLLER) & Vision6.takeSnapshot(Vision6__BLUE_ROLLER) or Vision6.takeSnapshot(Vision6__RED_ROLLER) & Vision6.takeSnapshot(Vision6__BLUE_ROLLER)){
    RollerWheel.spin(forward);
  }
  RollerWheel.stop();
}


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}



void autonomous(void) {
  /* always do this
    resetDriveSensors = true
    desiredValue = number
    desiredTurnValue = number

  */
  vex::task PID(drivePID);
  



}


void usercontrol(void) {
  enableDrivePID= false;
  while (1) {
    

    wait(20, msec); 
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
