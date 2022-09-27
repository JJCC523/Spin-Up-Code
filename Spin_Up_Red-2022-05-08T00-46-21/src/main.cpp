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
double kP = 0.009;
double kI = 0.00000;
double kD = 0.00;

double turnkP = 0.009;
double turnkI = 0.0000;
double turnkD = 0.00;

int desiredValue = 0;
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

bool resetDriveSensors=true;

int drivePID(){
  while(enableDrivePID){
    if(resetDriveSensors){
      RightSide.setPosition(0, degrees);
      LeftSide.setPosition(0, degrees);
      resetDriveSensors = false;

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
    error = desiredValue - averagePosition;

    //derivative
    derivative = prevError - error;

    //velocity > position > absement(position*time)
    totalError += error;

    double lateralMotorPower = ((error * kP) + (derivative * kD) + (totalError * kI)); 


///////////////////////////////////////////////////////////////////////////
//Turning movement PID
//////////////////////////////////////////////////////////////////////////

//average of the rotation
    int turnDifference = (LeftWheelPosition - RightWheelPosition);

    //potential
    turnError = desiredTurnValue + turnDifference;

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
    wait(20, msec);
  }

  return 1;
}

void pLoopRight(float degs){
  Inertial5.setHeading(0,degrees);
    while (Inertial5.heading(degrees)<degs){
    turnError = degs - Inertial5.heading(degrees);
    float MotorPower = turnError * turnkP;

    fL.spin(forward, MotorPower, percent);
    bL.spin(forward, MotorPower, percent);
    fR.spin(reverse, MotorPower, percent);
    bR.spin(reverse, MotorPower, percent);
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

void pLoopLeft(float degs){
  Inertial5.setHeading(359,degrees);
    while (Inertial5.heading(degrees)>degs){
    turnError = degs - Inertial5.heading(degrees);
    float MotorPower = turnError * turnkP;

    fL.spin(reverse, MotorPower, percent);
    bL.spin(reverse, MotorPower, percent);
    fR.spin(forward, MotorPower, percent);
    bR.spin(forward, MotorPower, percent);
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

void pLoopForward(float degs){
  Inertial5.setHeading(0,degrees);
    while (Inertial5.heading(degrees)<degs){
    error = degs - Inertial5.heading(degrees);
    float MotorPower = error * kP;

    fL.spin(forward, MotorPower, percent);
    bL.spin(forward, MotorPower, percent);
    fR.spin(forward, MotorPower, percent);
    bR.spin(forward, MotorPower, percent);
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

void pLoopReverse(float degs){
  Inertial5.setHeading(0,degrees);
    while (Inertial5.heading(degrees)<degs){
    error = degs - Inertial5.heading(degrees);
    float MotorPower = error * kP;

    fL.spin(forward, MotorPower, percent);
    bL.spin(forward, MotorPower, percent);
    fR.spin(reverse, MotorPower, percent);
    bR.spin(reverse, MotorPower, percent);
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

void rollerMech(){
  while(!Vision6.takeSnapshot(Vision6__RED_ROLLER) & Vision6.takeSnapshot(Vision6__BLUE_ROLLER) or Vision6.takeSnapshot(Vision6__RED_ROLLER) & Vision6.takeSnapshot(Vision6__BLUE_ROLLER)){
    RollerWheel.spin(forward);
  }
  RollerWheel.stop();
}


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial5.calibrate();
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
  desiredValue = 100;
  desiredTurnValue = 0;



}


void usercontrol(void) {
  enableDrivePID= false;
  while (1) {
    // Deadband stops the motors when Axis values are close to zero.
  int deadband = 5;

  while (true) {
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

 
    // Get the velocity percentage of the left motor. (Axis3 + Axis4)
    /*int leftMotorSpeed =
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
      fL.setVelocity(leftMotorSpeed+sideways, percent);
      bL.setVelocity(leftMotorSpeed - sideways, percent);

    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero. 
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      fR.setVelocity(0, percent);
      bR.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      fR.setVelocity(rightMotorSpeed - sideways, percent);
      bR.setVelocity(rightMotorSpeed + sideways, percent);
    }*/

    /*if (abs(sideways) < deadband) {
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

    }*/

    // Spin both motors in the forward direction.
    //fL.spin(forward);
    //fR.spin(forward);
    //bL.spin(forward);
    //bR.spin(forward);
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
