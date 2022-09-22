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
// fL                   motor         2               
// bL                   motor         9               
// fR                   motor         1               
// bR                   motor         10              
// Inertial5            inertial      5               
// RollerWheel          motor         7               
// Vision6              vision        6               
// RightSide            encoder       A, B            
// LeftSide             encoder       C, D            
// BackSide             encoder       E, F            
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here



//settings
double kP = 0.5;
double kI = 0.0;
double kD = 0.0;

double turnkP = 0.5;
double turnkI = 0.0;
double turnkD = 0.0;

int desiredValue;
int desiredTurnValue;

int error; //Sensor Value - Target Value : position
int prevError = 0; //position 20 msecs ago
int derivative; //error-prevError : speed
int totalError = 0; //TotalError= totalError + error

int turnError; //Sensor Value - Target Value : position
int turnPrevError = 0; //position 20 msecs ago
int turnDerivative; //error-prevError : speed
int turnTotalError = 0; //TotalError= totalError + error

bool enableDrivePID= true;

bool resetDriveSensors=true;

int drivePID(){
  while(enableDrivePID){
    if(resetDriveSensors){
      resetDriveSensors = false;

      RightSide.setPosition(0, degrees);
      LeftSide.setPosition(0, degrees);

    }

    //int GyroPosition = Inertial5.heading(degrees);
    //wheel position
    int LeftWheelPosition = LeftSide.position(degrees);
    int RightWheelPosition = RightSide.position(degrees);


///////////////////////////////////////////////////////////////////////////
//Lateral movement PID
//////////////////////////////////////////////////////////////////////////

    //average of the rotation
    int averagePosition = (LeftWheelPosition+RightWheelPosition)/2;

    //potential
    error =desiredValue - averagePosition;

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

  Controller1.Screen.print(LeftSide.rotation(degrees));
  Controller1.Screen.print(RightSide.rotation(degrees));

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}



void autonomous(void) {
  /* always do this
    resetDriveSensors = true
    desiredValue = number
    desiredTurnValue = number

  */
  resetDriveSensors = true;
  vex::task PID(drivePID);
  resetDriveSensors = true;
  desiredValue = 5;
  desiredTurnValue = 0;



}


void usercontrol(void) {
  enableDrivePID= false;
  while (1) {
    // Deadband stops the motors when Axis values are close to zero.
  int deadband = 5;

  while (true) {
    // Get the velocity percentage of the left motor. (Axis3 + Axis4)
    int leftMotorSpeed =
        Controller1.Axis3.position() + Controller1.Axis1.position();
    // Get the velocity percentage of the right motor. (Axis3 - Axis4)
    int rightMotorSpeed =
        Controller1.Axis3.position() - Controller1.Axis1.position();
    int sideways =
        Controller1.Axis4.position();

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      fL.setVelocity(0, percent);
      bL.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      fL.setVelocity(leftMotorSpeed, percent);
      bL.setVelocity(leftMotorSpeed, percent);

    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero. 
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      fR.setVelocity(0, percent);
      bR.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      fR.setVelocity(rightMotorSpeed, percent);
      bR.setVelocity(rightMotorSpeed, percent);
    }

    if (abs(sideways) < deadband) {
      // Set the speed to zero.
      fL.setVelocity(0, percent);
      bL.setVelocity(0, percent);
      fR.setVelocity(0, percent);
      bR.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      fL.setVelocity(sideways, percent);
      bR.setVelocity(sideways, percent);
      fR.setVelocity((sideways*-1), percent);
      bL.setVelocity((sideways*-1), percent);

    }

    // Spin both motors in the forward direction.
    fL.spin(forward);
    fR.spin(forward);
    bL.spin(forward);
    bR.spin(forward);
    wait(25, msec);
  }

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
