/*#include "vex.h"
#define Pi 3.14159625

//variables
  double X = 0;
  double Y = 0;
  
  double lastPosX = 0;
  double lastPosY = 0;
  double lastRot = 0;

  double xOffset = 0;
  double yOffset = 0;

double getRegularRot(){
  double curRotation = Inertial5.rotation();
  
  int times = (int)(curRotation/360);
  curRotation -= (360 * times);

  if(curRotation > 180)
  curRotation -= 360;
  else if(curRotation < 180){
  curRotation +=360;
  }
  return curRotation;
}

void update_pos(){
  //reset
    lastPosX = 0;
    lastPosY = 0;

    xEncoder.setPosition(0, degrees);
    yEncoder.setPosition(0, degrees);

  while(true){
    float xpos = xEncoder.position(degrees);
    float ypos = yEncoder.position(degrees);
    double curRotation = Inertial5.rotation(); 
    double changeInRot = curRotation - lastRot;
    if(fabs(changeInRot)<1)
      changeInRot = 0; //deadzone for IMU change

    double xDist = -(lastPosX - xpos);
    double yDist = -(lastPosY - ypos);
    xDist += (changeInRot * xOffset * Pi) / 180; //account for the offset of the x encoder

    xDist /= 100; //because the values that come out of this are too high
    yDist /= 100;

    lastPosX = xpos;
    lastPosY = ypos;
    lastRot = curRotation;

    //change x and y location of the robot based off of the rotation of the robot
    double rot = getRegularRot();
    double theta = rot*Pi/180;

    X += (sin(theta) * yDist) + (cos(theta) * xDist);
    Y += (cos(theta) * yDist) + (sin(-theta) * xDist);

    wait(10, msec);
  }
}*/