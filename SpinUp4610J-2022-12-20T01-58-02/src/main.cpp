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
// GyroA                gyro          A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "TheBrainThingy.cpp"
//#include "odomMove.cpp"


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
    while(Optical4.color() != blue || Optical40.color() != blue){
      roller.spin(forward, 75, percent);
      }
  roller.stop();
  takein = 2;
  rishiethefishiehatesjews = 0;
  }
  if (c == 2){
    while(Optical4.color() != red || Optical40.color() != red){
      roller.spin(forward, 75, percent);
      }
  roller.stop();
  takein = 2;
  rishiethefishiehatesjews = 0;

  }
  }
  }
  return(1);
}


/*int botInDiscs(){
  while(true){
    if(DiscSensor.objectDistance(mm)<70){
      takein=0;
    }
  else if (DiscSensor.objectDistance(mm)>70 && rishiethefishiehatesjews == 0){
      takein=1; 
  }
}
return(1);
}*/

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
void DF(float degs, int pwr){
  RightSide.setPosition(0,degrees);
  LeftSide.setPosition(0,degrees);
  fL.setPosition(0, degrees);
  float fwdthingy =  (RightSide.position(degrees)+LeftSide.position(degrees))/2;
    while (fwdthingy<degs){
    fwdthingy =  (RightSide.position(degrees)+LeftSide.position(degrees))/2;
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

void DFmotor(float degs, int pwr){
  RightSide.setPosition(0,degrees);
  LeftSide.setPosition(0,degrees);
  fL.setPosition(0, degrees);
  fwdAxis = 0;
    while (fL.position(degrees)<degs){
    

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


void SR(float degs){
  RightSide.setPosition(0,degrees);
  LeftSide.setPosition(0,degrees);
  fL.resetPosition();
    while (fL.position(degrees)<degs){
    error = degs - ((RightSide.position(degrees)*LeftSide.position(degrees))/2);

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
    while(215 < Optical4.hue() && 290 > Optical4.hue() ){
      roller.spin(forward, 50, percent);
      }
  roller.stop();
  takein = 2;
  }
  if (c == 2){
    while(Optical4.color() != red){
      roller.spin(forward, 50, percent);
      }
  roller.stop();
  takein = 2;
  }
}
int shootythingy = 0;

void shootdiscs(int discs, int flypower){
  int discs_shot = 0;
    while(discs_shot < discs){
      flywheel.spin(forward, flypower, percent);
      shootythingy = 1;
      Indexer = 1;
      wait(150,msec);
      Indexer = 0;
      shootythingy = 0;
      discs_shot = discs_shot+1;
      discsInBot = discsInBot - 1;
      wait(1,seconds);
    }
}
int detectDisc(){
  while(true){
  if(shootythingy == 0){
  if(DiscSensor.objectDistance(mm) > 110){
    Indexer = 1;
  }
  else{
    Indexer = 0;
  }
  wait (0.2, seconds); 
  }
  }
    return 0;

}
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
void Dtoroller(){
  while(!Optical40.isNearObject()){
    fL.spin(reverse, 50, percent);
    bL.spin(reverse, 50, percent);
    fR.spin(reverse, 50, percent);
    bR.spin(reverse, 50, percent);
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
int flypct = 65;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Indexer = 0;
  Endgame = 0;
  Endgame2 = 0;
  shootythingy = 0;
  Wall = 0;
  Inertial5.calibrate();
  discsInBot=0;
  flypct = 65;
  wait(3,seconds);
  while(true){
  //thread t(detectDisc);
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("RPM:%d",flypct);
  Controller1.Screen.setCursor(2,1);
  Controller1.Screen.print("Temp:%f",flywheel.velocity(rpm)*6 );
  Optical4.setLight(ledState::on);
  Optical4.setLightPower(100);
  Optical40.setLight(ledState::on);
  Optical40.setLightPower(100);
  //Controller1.Screen.setCursor(1,1);
  //if(DiscSensor.objectDistance(mm)<70){
  //Controller1.Screen.print("3");
  //}
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
      Brain.Screen.print("Oh Shit");

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
      Brain.Screen.print("Skills");

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
  setStartingPos(0, 0);
  thread t(forwardAxis);
  thread o(backgroundTasks);
  
  if(p == 1 && a == 1){
/*discsInBot=2;
  flywheel.spin(forward, 92, percent);
  DF(10, 100);
  Intake.spin(reverse, 50,percent);
  wait(0.4, sec); 
  Intake.stop();
  wait(100, msec);
  RollerMech();   
  DR(30);
  turnPIDCycle(-135, 100);
  turnPID(-135, 100, -1); 
  Intake.spin(forward, 100, percent); 
  DF(650, 100);
  turnPIDCycle(-90, 100);
  turnPID(-90, 100, -1);
  DFmotor(300, 100);
  wait(0.3, seconds); 
  DFmotor(10, 50);
  wait(0.1, seconds);
  RollerMech();
  getDegToPoint(-86.3 , 11.5);
  setTarget(-86.3 , 11.5);
  turnToTarget(100);
   shootdiscs(1, 82);
   wait(1, seconds);
  shootdiscs(2, 89);
  turnPIDCycle(-260, 100);
  turnPID(-260, 100, -1); 
  Intake.spin(forward, 100, percent);
  DF(400, 100);
  DF(700, 50);
  getDegToPoint(-86.3 , 11.5);
  setTarget(-86.3 , 11.5);
  turnToTarget(100);
  shootdiscs(3, 90);*/
  flywheel.spin(forward, 100, percent);
  DR(10);
  roller.spinFor(forward, 300, degrees);
  DFmotor(10, 50);
  turnPIDCycle(128, 100);
  turnPID(128, 100, -1);  
  flywheel.spin(forward, 100, percent);
  DR(1100);
  turnPIDCycle(43, 100);
  turnPID(43, 100, -1);
  waitUntil(flywheel.velocity(rpm)*6 >=2725);
  wait(0.2, seconds);
  shootdiscs(1, 100);
  waitUntil(flywheel.velocity(rpm)*6 >=2725 );
  shootdiscs(1, 100);
  turnPIDCycle(-42, 100);
  turnPID(-42, 100, -1);
  Intake.spin(forward, 75, percent);
  DFmotor(1200, 100);
  turnPIDCycle(-270, 100);
  turnPID(-270, 100, -1);
  DR(250);
  roller.spinFor(forward, 300, degrees);
  }
  if(p == 1 && a == 2){
  flywheel.spin(forward, 100, percent);
  DR(10);
  roller.spinFor(forward, 400, degrees);
  //DFmotor(10, 100);
  //turnPIDCycle(5, 100);
  //turnPID(5, 100, -1); 
  //waitUntil(flywheel.velocity(rpm)*6 >=2800);
  //shootdiscs(2, 100);
  DFmotor(10, 50);
  turnPIDCycle(-45, 100);
  turnPID(-45, 100, -1);  
  Intake.spin(forward,100,percent);
  flywheel.spin(forward, 100, percent);
  DFmotor(550, 100); 
  wait(0.1, seconds);
  DFmotor(200, 20);
  turnPIDCycle(23, 100);
  turnPID(23, 100, -1);
  DF(50, 100);  
  wait(0.5, seconds);
  waitUntil(flywheel.velocity(rpm)*6 >=2800);
  shootdiscs(1, 100);
  waitUntil(flywheel.velocity(rpm)*6 >=2800);
  shootdiscs(1, 100);
  waitUntil(flywheel.velocity(rpm)*6 >=2800);
  shootdiscs(1, 100); 
  waitUntil(flywheel.velocity(rpm)*6 >=2800);
  shootdiscs(1, 100);
  turnPIDCycle(-45, 100);
  turnPID(-45, 100, -1);
  wait(0.1, seconds);
  DFmotor(750, 50);  
  }
  if(p == 1 && a == 3){
  flywheel.spin(forward, 65, percent);
  DR(10);
  roller.spin(forward, 100, percent);
  wait(0.2, seconds);
  DFmotor(20, 100);
  Intake.spin(forward, 100, percent);
  turnPIDCycle(40, 100);
  turnPID(40, 100, -1);
  DFmotor(300, 50);
  turnPIDCycle(-90, 70);
  turnPID(-90, 70, -1);
  Dtoroller();
  roller.spin(forward, 100, percent);
  wait(0.2, seconds);  
  DFmotor(20, 100);
  turnPIDCycle(-2, 100);
  turnPID(-2, 100, -1);
  DFmotor(600, 100);
  turnPIDCycle(-1, 50);
  turnPID(-1, 50, -1);
  wait(0.5, seconds);
  shootdiscs(3, 65);
  flywheel.spin(forward, 65, percent);
  turnPIDCycle(-135, 70);
  turnPID(-135, 100, -1);
  DFmotor(200, 100);
  turnPIDCycle(-45, 100);
  turnPID(-45, 100, -1);
  DFmotor(1000, 70);
  turnPIDCycle(0, 100);
  turnPID(0, 100, -1);
  DFmotor(850, 100);
  turnPIDCycle(90, 100);
  turnPID(90, 100, -1);
  shootdiscs(3, 65);
  turnPIDCycle(85, 100);
  turnPID(85, 100, -1);
  DR(800);
  turnPIDCycle(180, 100);
  turnPID(180, 100, -1);
  DR(100);
  

  //Endgame = 1;
  //Endgame2 = 1;

  
  }
//Right Side & Red
  if(p == 2 && a == 4){
  setStartingPos(0, 0);
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
    setStartingPos(0, 0);
    flywheel.spin(forward, 96, percent);
    //turnPIDCycle(-12, 100);
    //turnPID(-12, 100, -1);
    turnPIDCycle(-85, 100);
    turnPID(-85, 100, 1500);
    DFmotor(300, 100);
    turnPIDCycle(0, 100);
    turnPID(0, 100, -1);     
    Dtoroller();
    roller.spinFor(forward, 300, degrees);
    DFmotor(5, 100);
    turnPIDCycle(45, 100);
    turnPID(45, 100, -1);
    Intake.spin(forward, 100, percent); 
    DFmotor(200, 100);
    DFmotor(500, 40);
    turnPIDCycle(-25, 100);
    turnPID(-25, 100, 2000);   
    waitUntil(flywheel.velocity(rpm)*6 >=2775);
    shootdiscs(1, 1000);
    waitUntil(flywheel.velocity(rpm)*6 >=2775);
    shootdiscs(1, 1000);
    waitUntil(flywheel.velocity(rpm)*6 >=2775);
    shootdiscs(1, 1000);
  }
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
  enableDrivePID= false;
    int takein = 1;
    timer Timer;
    Timer.reset();

  while (1) {
    // Deadband stops the motors when Axis values are close to zero.
  //int deadband = 5;
  shooter = 1;
  takein = 1;
  rishiethefishielovesjews = 1;
  rishiethefishiehatesjews = 1;
  int rightendgame = 0;
  int leftendgame = 0;
  while (true) {    
    thread t(rishithefishilovesandhatesjews);
    thread r(RollerMecch);
    thread a(backgroundTasks);
    //thread k(detectDisc);
    

    int forwardcontroller = Controller1.Axis3.position(percent);
    int sidewayscontroller= Controller1.Axis4.position(percent);
    int turncontroller= Controller1.Axis1.position(percent);

  fR.spin(forward, forwardcontroller-sidewayscontroller-turncontroller, percent);
  fL.spin(forward, forwardcontroller+sidewayscontroller+turncontroller, percent);
  bR.spin(forward, forwardcontroller+sidewayscontroller-turncontroller, percent);
  bL.spin(forward, forwardcontroller-sidewayscontroller+turncontroller, percent);

  /*if(DiscSensor.objectDistance(mm)<70){
      takein=0;
    }
  else if (DiscSensor.objectDistance(mm)>70 && rishiethefishiehatesjews == 0){
      takein=1; 
  }*/

  
   
    //if(Controller1.ButtonL1.pressing()){
      //takein=2;
    //}

    if(takein == 1){
      Intake.spin(forward, 100, percent);
    }
    if(takein == 0){
      Intake.stop();
      Intake.setStopping(hold); 
      roller.stop();
      roller.setStopping(hold); 
    }
    
    if(Controller1.ButtonLeft.pressing()){
      takein=3;
    }
    if(takein == 3){
      Intake.spin(reverse, 100, percent); 
    } 
 
    if(Controller1.ButtonR1.pressing()){
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
 
    if(rishiethefishielovesjews == 0){
  flypct = 80;

    }
    if(rishiethefishielovesjews == 1){
  flypct = 65;

    }
    if(Controller1.ButtonUp.pressing()){
      while(Controller1.ButtonUp.pressing()){
        wait(10, msec);
      }
      flypct=flypct+5;
  }
  if (flypct > 50 && flypct<80){
    rishiethefishielovesjews = -1;
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
  if(Controller1.ButtonL2.pressing() && Controller1.ButtonR2.pressing()){
    while(Controller1.ButtonL2.pressing() && Controller1.ButtonR2.pressing()){
      wait(10,msec);
    }      
      endgame_safe=endgame_safe+1;
  }
  

  if(Controller1.ButtonL2.pressing() && endgame_safe >= 1){
    while(Controller1.ButtonL2.pressing()){
      wait(10,msec);
    }      
    wallEndgame=wallEndgame+1;
      
  }
  if(Controller1.ButtonR2.pressing() && endgame_safe >= 1){
    while(Controller1.ButtonR2.pressing()){
      wait(10,msec);
    }      
      rightendgame=rightendgame+1;
      leftendgame=leftendgame+1;
  }

  if (rightendgame >= 1){
    Endgame2 = 1;
  }
  if (leftendgame >= 1){
    Endgame = 1;
  }
  if (wallEndgame >= 1){
    Wall = 1;
  }
  if(Timer.time() < 95000){
    fL.setStopping(coast); 
    fR.setStopping(coast);
    bR.setStopping(coast);
    bL.setStopping(coast);
  }
  else if (Timer.time() > 95000) {
    fL.setStopping(hold); 
    fR.setStopping(hold);
    bR.setStopping(hold);
    bL.setStopping(hold);
  }
  
  flywheel.setVelocity(flypct, percent);

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