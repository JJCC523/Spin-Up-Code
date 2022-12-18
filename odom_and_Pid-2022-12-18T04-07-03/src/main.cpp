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
}



void autonomous(void) { 
  thread t(forwardAxis);
  c = 1;
  //first half
  DF(10,100);
  RollerMech();
  forwardPID(-1, 100, -1);
  Intake.spin(forward, 100, percent);
  turnPID(186, 100, -1);
  shootdiscs(2, 92);
  turnPID(-45, 60 , -1);
  forwardPID(25, 100, -1);
  turnPID(-45, 60, -1);
  Intake.stop();
  DF(30, 100);
  RollerMech();
  DR(20);
  Intake.spin(forward, 100, percent);
  turnPID(97, 100, -1);
  forwardPID(12, 100, -1);
  shootdiscs(1, 78);
  turnPID(38, 100, -1);
  forwardPID(69, 100, -1);
  turnPID(-90, 100, -1);
  shootdiscs(3, 74);
  turnPID(90, 100, -1);
  forwardPID(38, 60, -1);
  turnPID(-125, 100, -1);
  shootdiscs(3, 78);
  turnPID(125, 100, -1);
  forwardPID(28.5, 100, -1);
  turnPID(-45, 100, -1);
  Intake.stop();
  DF(50, 100);
  //second half
  RollerMech();
  forwardPID(-1, 100, -1);
  Intake.spin(forward, 100, percent);
  turnPID(186, 100, -1);
  shootdiscs(2, 92);
  turnPID(-45, 60 , -1);
  forwardPID(25, 100, -1);
  turnPID(-45, 60, -1);
  Intake.stop();
  DF(30, 100);
  RollerMech();
  DR(20);
  Intake.spin(forward, 100, percent);
  turnPID(97, 100, -1);
  forwardPID(12, 100, -1);
  shootdiscs(1, 78);
  turnPID(38, 100, -1);
  forwardPID(69, 100, -1);
  turnPID(-90, 100, -1);
  shootdiscs(3, 74);
  turnPID(90, 100, -1);
  forwardPID(38, 60, -1);
  turnPID(-125, 100, -1);
  shootdiscs(3, 78);
  turnPID(125, 100, -1);
  forwardPID(28.5, 100, -1);
  turnPID(180, 100, -1);
  Endgame = 1;
  wait(200, msec);
  Endgame = 0;
  wait(200, msec);
  Endgame = 1;
  wait(200, msec);
  Endgame = 0;
}

  
int rishiethefishielovesjews = 0;
int shooter = 0;

void usercontrol(void) {
  enableDrivePID= false;
    int takein = 1;
 
    

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
