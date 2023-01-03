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
// Expander11           triport       11              
// RightSide            encoder       A, B            
// LeftSide             encoder       C, D            
// BackSide             encoder       E, F            
// DiscSensor           line          A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "TheBrainThingy.cpp"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
double fwdAxis = 0;
int forwardAxis(){
  while(true){
    fwdAxis = (RightSide.position(degrees)+LeftSide.position(degrees))/2;
  }
  return(1);
}
int takein=0;
int discsInBot = 0;
int rishiethefishiehatesjews = 0;
int c = 0;

int RollerMecch(){
  while(true){
  if(Controller1.ButtonRight.pressing()){
    rishiethefishiehatesjews = 1;
  if (c == 1){
    while(Optical4.color() != blue){
      Intake.spin(reverse, 30, percent);
      }
  Intake.stop();
  takein = 2;
  rishiethefishiehatesjews = 0;
  }
  if (c == 2){
    while(Optical4.color() != red){
      Intake.spin(reverse, 30, percent);
      }
  Intake.stop();
  takein = 2;
  rishiethefishiehatesjews = 0;

  }
  }
  }
  return(1);
}


int botInDiscs(){
  while(true){
    if(DiscSensor.objectDistance(mm)<70){
      takein=0;
    }
  else if (DiscSensor.objectDistance(mm)>70 && rishiethefishiehatesjews == 0){
      takein=1; 
  }
}
return(1);
}

int p = 0;
int a = 0;
int f = 0;

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

//double fwdAxis =(RightSide.rotation(degrees)+LeftSide.rotation(degrees))/2;
//float sideAxis = BackSide.rotation(degrees);

void TR(float degs){
    Inertial5.setHeading(5, degrees);
    Inertial5.resetRotation();

    while (Inertial5.heading(degrees)<degs){

    error = degs - Inertial5.rotation(degrees);
    float MotorPower = error * 0.7;

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

void TL(float degs){
  Inertial5.setHeading(358, degrees);
  Inertial5.resetRotation();
    while (Inertial5.rotation(degrees)>(degs)){

    error = (degs) + Inertial5.rotation(degrees);
    float MotorPower = error * 1.2;

    fL.spin(reverse, 50, percent);
    bL.spin(reverse, 50, percent);
    fR.spin(forward, 50, percent);
    bR.spin(forward, 50, percent);
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
  //float fwdAxis = ((RightSide.position(degrees)+LeftSide.position(degrees))/2);

void DF(float degs, int pwr){
  RightSide.setPosition(0,degrees);
  LeftSide.setPosition(0,degrees);
  fL.setPosition(0, degrees);
  fwdAxis = 0;
    while (fwdAxis<degs){
    

    fL.spin(forward, pwr, percent);
    bL.spin(forward, pwr, percent);
    fR.spin(forward, pwr, percent);
    bR.spin(forward, pwr, percent);
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

void DR(float degs){
  RightSide.setPosition(0,degrees);
  LeftSide.setPosition(0,degrees);
  fL.resetPosition();
    while (fL.position(degrees)>(degs*-1)){
    error = degs - ((RightSide.position(degrees)*LeftSide.position(degrees))/2);
    float MotorPower = error * kP;

    fL.spin(reverse, 100, percent);
    bL.spin(reverse, 100, percent);
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
void intaketakein (){
  while(discsInBot<3){
    Intake.spin(forward, 100, percent);
    if(DiscSensor.objectDistance(mm)<36){
      discsInBot = discsInBot+1;
    } 
  }
  Intake.stop();

}

void SR(float degs){
  RightSide.setPosition(0,degrees);
  LeftSide.setPosition(0,degrees);
  fL.resetPosition();
    while (fL.position(degrees)<degs){
    error = degs - ((RightSide.position(degrees)*LeftSide.position(degrees))/2);
    float MotorPower = error * kP;

    fL.spin(forward, 100, percent);
    bL.spin(forward, 100, percent);

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

void STR(float degs){
  RightSide.setPosition(0,degrees);
  LeftSide.setPosition(0,degrees);
  BackSide.setPosition(0, degrees);
  fL.resetPosition();
    while (BackSide.position(degrees)<degs){
    error = degs - ((RightSide.position(degrees)*LeftSide.position(degrees))/2);
    float MotorPower = error * kP;

    fL.spin(forward, 100, percent);
    bL.spin(reverse, 100, percent);
    fR.spin(reverse, 100, percent);
    bR.spin(forward, 100, percent);

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

void STL(float degs){
  RightSide.setPosition(0,degrees);
  LeftSide.setPosition(0,degrees);
  fR.resetPosition();
  BackSide.setPosition(0, degrees);
  fL.resetPosition();
    while (BackSide.position(degrees)<degs){
    error = degs - ((RightSide.position(degrees)*LeftSide.position(degrees))/2);
    float MotorPower = error * kP;

    fL.spin(reverse, 100, percent);
    bL.spin(forward, 100, percent);
    fR.spin(forward, 100, percent);
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


void RollerMech(){
  if (c == 1){
    while(Optical4.color() != blue){
      Intake.spin(reverse, 30, percent);
      }
  Intake.stop();
  takein = 2;
  }
  if (c == 2){
    while(Optical4.color() != red){
      Intake.spin(reverse, 30, percent);
      }
  Intake.stop();
  takein = 2;
  }
}

void shootdiscs(int discs, int flypower){
  int discs_shot = 0;
    while(discs_shot < discs){
      flywheel.spin(forward, flypower, percent);
      Indexer = 1;
      wait(200,msec);
      Indexer = 0;
      discs_shot = discs_shot+1;
      discsInBot = discsInBot - 1;
      wait(1,seconds);
    }
}
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial5.calibrate();
  discsInBot=0;
  wait(3,seconds);
  while(true){
    thread t(botInDiscs);
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("RPM:%f",flywheel.velocity(rpm)*5);
  Controller1.Screen.setCursor(2,1);
  Controller1.Screen.print("Temp:%f",flywheel.temperature(celsius));

  Controller1.Screen.setCursor(1,1);
  if(DiscSensor.objectDistance(mm)<70){
  Controller1.Screen.print("3");
  }
  wait(50,msec); 
  Controller1.Screen.clearScreen();
  gui::thatthingyoupress RedSide(5,5);
  Brain.Screen.setCursor(4,2);
  Brain.Screen.print("Red");
  gui::thatthingyoupress BlueSide(75,5);
  Brain.Screen.setCursor(4,9);
  Brain.Screen.print("Blue");
  gui::thatthingyoupress PosLeft(5,100); 
  Brain.Screen.setCursor(9,2);
  Brain.Screen.print("Left");
  gui::thatthingyoupress PosRight(75,100);
  Brain.Screen.setCursor(9,9);
  Brain.Screen.print("Right");
  Brain.Screen.setCursor(1,30);
  Brain.Screen.print("Color:");
  Brain.Screen.setCursor(2,31);
  Brain.Screen.print("Side:");
  Brain.Screen.setCursor(3,30);
  Brain.Screen.print("Auton:");
  if(RedSide.pressed()){
  while(RedSide.pressed()){
    wait(10,msec);
  }
  if(c != 1)
  c=1;
  }
  if(BlueSide.pressed()){
  while(BlueSide.pressed()){
    wait(10,msec);
  }
  if(c != 2)
  c=2;
  }
  if(PosLeft.pressed()){
  while(PosLeft.pressed()){
    wait(10,msec);
  }
  if(p != 1)
  p=1;
  }
  if(p==1){
  Brain.Screen.setFillColor(black);
  Brain.Screen.setPenColor(black);
  Brain.Screen.drawRectangle(195, 100, 210, 150);
  Brain.Screen.setPenColor(white);
  gui::thatthingyoupress Auto1(200,100); 
  Brain.Screen.setCursor(9,21);
  Brain.Screen.print("Auto 1");
  gui::thatthingyoupress Auto2(270,100); 
  Brain.Screen.setCursor(9,28);
  Brain.Screen.print("Auto 2");
  gui::thatthingyoupress Auto3(340,100); 
  Brain.Screen.setCursor(9,35);
  Brain.Screen.print("Auto 3");
  if(Auto1.pressed()){
  while(Auto1.pressed()){
    wait(10,msec);
  }
  if(a != 1)
  a=1;
  }
  if(Auto2.pressed()){
  while(Auto2.pressed()){
    wait(10,msec);
  }
  if(a != 2)
  a=2;
  }
  if(Auto3.pressed()){
  while(Auto3.pressed()){
    wait(10,msec);
  }
  if(a != 3)
  a=3;
  }
  }
  if(p==2){
  Brain.Screen.setFillColor(black);
  Brain.Screen.setPenColor(black);
  Brain.Screen.drawRectangle(195, 100, 210, 150);
  Brain.Screen.setPenColor(white);
  gui::thatthingyoupress Auto1(200,100);
  Brain.Screen.setCursor(9,21);
  Brain.Screen.print("Auto 1");
  gui::thatthingyoupress Auto5(270,100); 
  Brain.Screen.setCursor(9,28);
  Brain.Screen.print("Auto 2");
  if(Auto1.pressed()){
  while(Auto1.pressed()){
    wait(10,msec);
  }
  if(a != 4)
  a=4;
  }
  if(Auto5.pressed()){
  while(Auto5.pressed()){
    wait(10,msec);
  }
  if(a != 5)
  a=5;
  }
  }
  if(PosRight.pressed()){
  while(PosRight.pressed()){
    wait(10,msec);
  }
  if(p != 2)
  p=2;

  }
  if(c == 1 && p == 1 && a == 1){
      Brain.Screen.setCursor(1, 36);
      Brain.Screen.print("Red");
      Brain.Screen.setPenColor(black);
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(2,36);
      Brain.Screen.print("Left Side");
      Brain.Screen.setPenColor(black);
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.print("Full WP");

  }
  if(c == 1 && p == 1 && a == 2){
      Brain.Screen.setCursor(1, 36);
      Brain.Screen.print("Red");
      Brain.Screen.setPenColor(black);
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(2,36);
      Brain.Screen.print("Left Side");
      Brain.Screen.setPenColor(black);
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.setPenColor(black); 
      Brain.Screen.print("Full WP");
      Brain.Screen.setPenColor(white); 
      Brain.Screen.setCursor(3,36);
      Brain.Screen.print("Half WP");

  }
  if(c == 1 && p == 1 && a == 3){
      Brain.Screen.setCursor(1, 36);
      Brain.Screen.print("Red");
      Brain.Screen.setPenColor(black);
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(2,36);
      Brain.Screen.print("Left Side");
      Brain.Screen.setPenColor(black);
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.setPenColor(black); 
      Brain.Screen.print("Full WP");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.print("3");

  }
  if(c == 1 && p == 2 && a == 4){
      Brain.Screen.setCursor(1, 36);
      Brain.Screen.print("Red");
      Brain.Screen.setPenColor(black);
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(2,36);
      Brain.Screen.print("Right Side");
      Brain.Screen.setCursor(3,36);
      Brain.Screen.print("Not WP");

  }
  if(c == 1 && p == 2 && a == 5){
      Brain.Screen.setCursor(1, 36);
      Brain.Screen.print("Red");
      Brain.Screen.setPenColor(black);
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(2,36);
      Brain.Screen.print("Right Side");
      Brain.Screen.setCursor(3,36);
      Brain.Screen.print("2");

  }
  if(c == 2 && p == 1 && a == 1){
      Brain.Screen.setCursor(1, 36);
      Brain.Screen.print("Blue");
      Brain.Screen.setCursor(2,36);
      Brain.Screen.print("Left Side");
      Brain.Screen.setPenColor(black); 
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.print("Full WP");

  }
  if(c == 2 && p == 1 && a == 2){
      Brain.Screen.setCursor(1, 36);
      Brain.Screen.print("Blue");
      Brain.Screen.setCursor(2,36);
      Brain.Screen.print("Left Side");
      Brain.Screen.setPenColor(black); 
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.setPenColor(black); 
      Brain.Screen.print("Full WP");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.print("Half WP");

  }
  if(c == 2 && p == 1 && a == 3){
      Brain.Screen.setCursor(1, 36);
      Brain.Screen.print("Blue");
      Brain.Screen.setCursor(2,36);
      Brain.Screen.print("Left Side");
      Brain.Screen.setPenColor(black); 
      Brain.Screen.print("e");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.setPenColor(black); 
      Brain.Screen.print("Full WP");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.print("3");

  }
  if(c == 2 && p == 2 && a == 4){
      Brain.Screen.setCursor(1, 36); 
      Brain.Screen.print("Blue");
      Brain.Screen.setCursor(2,36);
      Brain.Screen.print("Right Side");
      Brain.Screen.setCursor(3,36);
      Brain.Screen.setPenColor(black); 
      Brain.Screen.print("Full WP");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.print("Not WP");

  }
  if(c == 2 && p == 2 && a == 5){
      Brain.Screen.setCursor(1, 36); 
      Brain.Screen.print("Blue");
      Brain.Screen.setCursor(2,36);
      Brain.Screen.print("Right Side");
      Brain.Screen.setCursor(3,36);
      Brain.Screen.setPenColor(black); 
      Brain.Screen.print("Full WP");
      Brain.Screen.setPenColor(white);
      Brain.Screen.setCursor(3,36);
      Brain.Screen.print("2");

  }
  gui::thatthingyoupress LockIn(425,170); 
  Brain.Screen.setCursor(50,42);
  Brain.Screen.print("Lock In");
  if(LockIn.pressed()){
    while(LockIn.pressed()){
    wait(10,msec);
  }
  if(f != 1)
  f=1;
  }
  if(f == 1){
  Brain.Screen.setFillColor(black);
  Brain.Screen.setPenColor(black);
  Brain.Screen.drawRectangle(0, 0, 500, 500);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setCursor(1,30);
  Brain.Screen.print("Color:");
  if(c==1){
    Brain.Screen.setCursor(1,36);
    Brain.Screen.print("Red");
  }
  if(c==2){
    Brain.Screen.setCursor(1,36);
    Brain.Screen.print("Blue");
  }
  Brain.Screen.setCursor(2,31);
  Brain.Screen.print("Side:");
  if(p==1){
    Brain.Screen.setCursor(2,36);
    Brain.Screen.print("Left Side");
  }
  if(p==2){
    Brain.Screen.setCursor(2,36);
    Brain.Screen.print("Right Side");
  }
  Brain.Screen.setCursor(3,30);
  Brain.Screen.print("Auton:");
  if(a==1 or a==2 or a == 3){
    Brain.Screen.setCursor(3,36);
    Brain.Screen.print(a);
  }
  if(a==4){
    Brain.Screen.setCursor(3,36);
    Brain.Screen.print("1");
  }
  if(a==5){
    Brain.Screen.setCursor(3,36);
    Brain.Screen.print("2");
  }
  }
  wait (250, msec);
  }
  
    wait(20,msec);
    takein=0;
  

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}



void autonomous(void) { 
  thread t(forwardAxis);
  if(p == 1 && a == 1){
  discsInBot=2;
  flywheel.spin(forward, 100, percent);
  DF(30, 100);
  Intake.spin(reverse, 50,percent);
  wait(0.4, sec); 
  Intake.stop();
  wait(100, msec);
  RollerMech();  
  DR(50);
  turnPIDCycle(180, 100);
  turnPID(180, 100, -1);
  shootdiscs(2, 89);
  //above is tested
  turnPIDCycle(129, 100);
  turnPID(129, 100, -1);  
  Intake.spin(forward,100,percent);
  DF(800, 100);
  wait(0.1, seconds);
  DF(800, 50);
  turnPIDCycle(214, 100);
  turnPID(214, 100, -1); 
  shootdiscs(3,75);
  turnPIDCycle(135, 100);
  turnPID(135, 100, -1);  
  Intake.spin(forward,100,percent); 
  DF(1900,100);
  Intake.spin(forward,100,percent);
  turnPIDCycle(90, 100);
  turnPID(90, 100, -1);
  RollerMech();
  }
  if(p == 1 && a == 2){
  flywheel.spin(forward, 100, percent);
  DF(15, 100);
  Intake.spin(reverse, 50,percent);
  wait(0.1, sec); 
  Intake.stop(); 
  wait(100, msec);
  RollerMech();  
  DR(20);
  turnPIDCycle(177, 100);
  turnPID(177, 100, -1);
  wait(0.5, seconds); 
  shootdiscs(2, 88);
  //above is tested
  turnPIDCycle(135, 100);
  turnPID(135, 100, -1);
  Intake.spin(forward,100,percent);
  DF(1400, 80);
  turnPIDCycle(225, 100);
  turnPID(225, 100, -1);  
  shootdiscs(3,68);
  }
  if(p == 1 && a == 3){
  
  }
//Right Side & Red
  if(p == 2 && a == 4){
  flywheel.spin(forward, 100, percent);
  SR(4000);
  Intake.spin(reverse, 50,percent);
  wait(0.2, sec);
  RollerMech();
  DR(80);
  TR(190); 
  wait(0.5, seconds);
  STR(200);
  shootdiscs(2,95);
  STL(500);
  TR(45);
  STL(300);
  Intake.spin(forward, 100,percent);
  DF(300, 100);
  DR(200);
  TL(20);
  shootdiscs(3, 95);
  }
  if(p == 2 && a == 5){
    flywheel.spin(forward, 96, percent);
    //turnPIDCycle(-22, 50);
    //turnPID(-22, 50, -1);
    wait(1.3, sec); 
    shootdiscs(2, 95);
    turnPIDCycle(-90, 100);
    turnPID(-90, 100, 1500);
    DF(350, 100);
    turnPIDCycle(-180, 100);
    turnPID(-180, 100, -1);    
    DF(65, 100);
    Intake.spin(reverse,25,percent);
    wait(0.5, sec);
    RollerMech();
    DR(30);
    STR(550);
    turnPIDCycle(-315, 100);
    turnPID(-315, 100, 2000);   
    Intake.spin(forward, 100, percent); 
    DF(1250, 100);
    turnPIDCycle(-410, 100);
    turnPID(-410, 100, -1);
    shootdiscs(4, 83);
  }
}

  
int rishiethefishielovesjews = 0;
int shooter = 0;

void usercontrol(void) {
  enableDrivePID= false;
    int takein = 1;
  setStartingPos(5, 5);
    

  while (1) {
    // Deadband stops the motors when Axis values are close to zero.
  int deadband = 5;
  shooter = 1;
  takein = 1;
  while (true) {
    thread t(botInDiscs);
    thread r(RollerMecch);
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

if(DiscSensor.objectDistance(mm)<70){
      takein=0;
    }
  else if (DiscSensor.objectDistance(mm)>70 && rishiethefishiehatesjews == 0){
      takein=1; 
  }

  if(Controller1.ButtonDown.pressing()){
    while(Controller1.ButtonDown.pressing()){
      wait(10,msec);
    }      
      takein=takein+1;
    if(takein > 1){
        takein=0;
      }
  }
  
   
    //if(Controller1.ButtonL1.pressing()){
      //takein=2;
    //}

    if(takein == 1){
      Intake.spin(forward, 100, percent);
    }
    if(takein == 0){
      Intake.stop();
      Intake.setStopping(hold); 
    }
    
    if(Controller1.ButtonLeft.pressing()){
      takein=3;
    }
    if(takein == 3){
      Intake.spin(reverse, 100, percent); 
    } 
 
    if(Controller1.ButtonB.pressing()){
      wait(10, msec);
      Indexer = 1; 
      wait(150,msec);
      Indexer = 0;
    }  

    
if(Controller1.ButtonY.pressing()){
      
    while(Controller1.ButtonY.pressing()){
        wait(10,msec);
      }      
  shooter = shooter+1;
    if(shooter > 1){
        shooter=0;
      }
      
    }
    if(shooter == 1){
      flywheel.spin(forward, 100, percent);
    }
    if(shooter == 0){
      flywheel.stop();
    }

    if(Controller1.ButtonL1.pressing()){
      while(Controller1.ButtonL1.pressing()){
        wait(10, msec);
      }
      rishiethefishielovesjews=rishiethefishielovesjews+1;
    if(rishiethefishielovesjews > 1){
      rishiethefishielovesjews = 0;
    }
    }

    if(rishiethefishielovesjews == 1){
      flywheel.setVelocity(100, percent);
    }
    if(rishiethefishielovesjews == 0){
      flywheel.setVelocity(77, percent);
    }

  if(Controller1.ButtonR2.pressing()){
    wait(10, msec);
    Endgame = 1; 
    wait(150,msec);
    Endgame = 0;
  }

  //if(Controller1.ButtonLeft.pressing()){
    //getDegToPoint(5, 5);
    //setTarget(5, 5);
    //turnToTarget(50);
  //}

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
