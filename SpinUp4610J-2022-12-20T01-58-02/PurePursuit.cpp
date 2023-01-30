
#include "vex.h"

double lookahead = 5; // Lookahead distance in inches
double k = 0.5; // Proportional gain constant
double maxSpeed = 50; // Maximum speed in RPM
double robotRadius = 9; //Robot radius in inches
double wheelBase = 17; // Wheel base in inches

double getRobotSpeed() {
  // Calculate robot speed in inches/sec
  return (LeftMotor.velocity(vex::velocityUnits::pct) + 
          RightMotor.velocity(vex::velocityUnits::pct)) / 2;
}

double getTargetAngle(double x, double y) {
  // Calculate target angle based on lookahead distance
  double l = sqrt(pow(x, 2) + pow(y, 2));
  return atan2(lookahead * (y / l), lookahead * (x / l));
}

double getTurnRadius(double targetAngle) {
  // Calculate turn radius based on target angle
  return (wheelBase / 2) * (tan(targetAngle));
}

void driveToPoint(double x, double y) {
  // Calculate target angle and turn radius
  double targetAngle = getTargetAngle(x, y);
  double turnRadius = getTurnRadius(targetAngle);

  // Calculate robot speed
  double robotSpeed = getRobotSpeed();

  // Calculate left and right motor speeds
  double leftSpeed = robotSpeed * ((2 * robotRadius) / (robotRadius + turnRadius));
  double rightSpeed = robotSpeed * ((2 * robotRadius) / (robotRadius - turnRadius));

  // Set motor speeds
  LeftMotor.spin(vex::directionType::fwd, leftSpeed * k, vex::velocityUnits::rpm);
  RightMotor.spin(vex::directionType::fwd, rightSpeed * k, vex::velocityUnits::rpm);
}