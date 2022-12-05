/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\jack0                                            */
/*    Created:      Sun Dec 04 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor_group   1, 2            
// rightMotor           motor_group   3, 4            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// define the wheel diameter
#define WHEEL_DIAMETER 4.0

// define the wheel circumference
#define WHEEL_CIRCUMFERENCE (WHEEL_DIAMETER * 3.14159)

// define the encoder counts per revolution
#define ENCODER_COUNTS_PER_REVOLUTION 360

// define the distance per encoder count
#define DISTANCE_PER_ENCODER_COUNT (WHEEL_CIRCUMFERENCE / ENCODER_COUNTS_PER_REVOLUTION)

// define the left and right motor objects

// define the odometry variables
double x = 0;
double y = 0;
double theta = 0;

// define the previous encoder values
int prevLeftEncoder = 0;
int prevRightEncoder = 0;

// define the odometry update function
void updateOdometry() {
  // get the current encoder values
  int currLeftEncoder = leftMotor.rotation(vex::rotationUnits::deg);
  int currRightEncoder = rightMotor.rotation(vex::rotationUnits::deg);

  // calculate the distance traveled by each wheel
  double leftDistance = (currLeftEncoder - prevLeftEncoder) * DISTANCE_PER_ENCODER_COUNT;
  double rightDistance = (currRightEncoder - prevRightEncoder) * DISTANCE_PER_ENCODER_COUNT;

  // calculate the distance traveled by the robot
  double distance = (leftDistance + rightDistance) / 2.0;

  // calculate the change in angle
  double deltaTheta = (rightDistance - leftDistance) / WHEEL_DIAMETER;

  // update the odometry variables
  x += distance * cos(theta);
  y += distance * sin(theta);
  theta += deltaTheta;

  // save the current encoder values for the next iteration
  prevLeftEncoder = currLeftEncoder;
  prevRightEncoder = currRightEncoder;
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}
