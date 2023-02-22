#include "vex.h"
#include "odomtrack.cpp"

double targetDeg = 0;
double targetDistance = 0;


double rotToPoint(double x, double y)
{
  double relativeX = x - X;
  double relativeY = y - Y;

  // atan2(y, x) gives the absolute angle from the origin to the specified point
  // This is the angle to turn to to get from the current point to the target point
  double deg = toDegrees * atan2(relativeY, relativeX);

  // Prevent the robot from targeting a rotation over 180 degrees from its current rotation.
  // If it's more than 180 it's faster to turn the other direction
  deg = angleWrap(deg);
  
  return deg;
}



void TTP(float getX, float getY, double maxTurnSpeed)
{
  double finalTurnSpeed = 1;

  while (finalTurnSpeed != 0) // If within acceptable distance, PID output is zero.
  {
    targetDeg = getDegToPoint(getX, getY); // Obtain the closest angle to the target position

    finalTurnSpeed = turnPIDCycle(targetDeg, maxTurnSpeed); // Plug angle into turning PID and get the resultant speed
    
      // Turn in place towards the position
    setLeftBase(-finalTurnSpeed);
    setRightBase(finalTurnSpeed);
    
    task::sleep(5);
  }
  
}

void MTP(float getX, float getY, double maxFwdSpeed, double maxTurnSpeed)
{
  resetTotalDistance();
//turn
  double finalTurnSpeed = 1;

  while (finalTurnSpeed != 0) // If within acceptable distance, PID output is zero.
  {
    targetDeg = getDegToPoint(getX, getY); // Obtain the closest angle to the target position

    finalTurnSpeed = turnPIDCycle(targetDeg, maxTurnSpeed); // Plug angle into turning PID and get the resultant speed
    
      // Turn in place towards the position
    setLeftBase(-finalTurnSpeed);
    setRightBase(finalTurnSpeed);
    
    task::sleep(5);
  }
//drive
  double curFwdSpeed = 1;

  targetDistance = getDistanceTo(getX, getY);

   while (curFwdSpeed != 0 && fabs(targetDistance) > 3/* && !isStopped()*/)
  {
    targetDistance = getDistanceTo(getX, getY);
    targetDeg = getDegToPoint(getX, getY);
    
    curFwdSpeed = fwdPIDCycle(targetDistance, maxFwdSpeed); // calculate pid forward speed
    
    setLeftBase(curFwdSpeed);
    setRightBase(curFwdSpeed);
    Brain.Screen.printAt(210, 120, "target: (%.1f, %.1f) %.1f deg", getX, getY, targetDeg);
    task::sleep(5);
  }
}