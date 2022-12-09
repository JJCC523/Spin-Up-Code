#include "vex.h"

using namespace vex;

class drivebase {
  float radius;
  double kp;
  double ki;
  double kd;
  drivebase(float radius, double kp, double ki, double kd) {
    this -> radius = radius;
    this -> kp = kp;
    this -> ki = ki;
    this -> kd = kd;
    thread  (positiontrack());
  }
  float x= 0;
  float y = 0;
  float head = 0;
  void dnf(int x1,int y1, int r1){
    
    while(x1 !=x && y1!=y) {
    float xdif = x1-x;
    float ydif = y1-y;
    float rdif = r1-head;

    fl.spin(forward, xdif+ydif+rdif,pct);
    bl.spin(forward, xdif-ydif+rdif,pct);
    fr.spin(forward, xdif-ydif-rdif,pct);
    br.spin(forward, xdif+ydif-rdif,pct);
    }
    fl.stop();
    fr.stop();
    bl.stop();
    br.stop();

  }

  int positiontrack() {
    float theta =0;
    
    
    while (true)
    {
      head = Inertial1.rotation(degrees);
      Xrot.resetPosition();
      Yrot.resetPosition();
      wait(10, msec);
      theta = Inertial1.rotation(degrees) - head;
      float k = (180 - theta)/2 + head;
      float rad1 = 180*(Xrot.position(degrees)*(2*radius*3.14159/360))/(theta*3.14159);
      float rad2 = 180*Yrot.position(degrees)*(2*radius*3.14159/360)/(theta*3.14159);
      float Chord1 = 2*rad1*sin((Xrot.position(degrees)/(2*rad1))*3.14159/180);
      float Chord2 = 2*rad2*sin((Yrot.position(degrees)/(2*rad2))*3.14159/180);
      x = x+ sin(k*3.14159/180)*Chord2 + cos(k*3.14159/180)*Chord1;
      y = y+ sin(k*3.14159/180)*Chord1 + cos(k*3.14159/180)*Chord2;
    }
    return 0;
  }
  





};