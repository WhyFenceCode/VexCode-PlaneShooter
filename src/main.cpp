/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\whyfe                                            */
/*    Created:      Mon Jan 30 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// MotorA               motor         1               
// MotorB               motor         9               
// MotorC               motor         11              
// MotorD               motor         19              
// UpMotor              motor         17              
// ReLoadMotor          motor         6               
// MagMotors            motor_group   12, 13          
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

bool fireing = false;
bool canFire = true;
float UpMotorDist = 90;
float SlideMotorDist = 90;
float MagDist = 90;
int FullMag = 10;
int Mag = FullMag;
bool reMessage = false;

void Launch(){
  //Change Fire State
  if (fireing == true){
    return;
  }else if (fireing == false){
    fireing = true;
  }

}

void Fire(){
  //Fire In The Hole
  UpMotor.spinFor(forward, UpMotorDist, degrees);
}

void Reload(){
  //Reload The Barrel
  ReLoadMotor.spinFor(forward, SlideMotorDist, degrees);
  UpMotor.spinFor(forward, -UpMotorDist, degrees);
  ReLoadMotor.spinFor(forward, -SlideMotorDist, degrees);
  MagMotors.spinFor(forward, MagDist, degrees);
  Mag --;
}

void Run(){
  
  for(;;){  
    double a = 0, b = 0, c = 0, d = 0;
    a -= Controller1.Axis3.position(percent);
    b -= Controller1.Axis3.position(percent);
    c += Controller1.Axis4.position(percent);
    d += Controller1.Axis4.position(percent);
    

    if(Controller1.ButtonR2.pressing()){
      a += 25;
      b -= 25;
      c += 25;
      d -= 25;
    }

    if(Controller1.ButtonL2.pressing()){
      a -= 25;
      b += 25;
      c -= 25;
      d += 25;
    }

    if(Controller1.ButtonR1.pressing()){
      a += 10;
      b -= 10;
      c += 10;
      d -= 10;
    }

    if(Controller1.ButtonL1.pressing()){
      a -= 10;
      b += 10;
      c -= 10;
      d += 10;
    }

    if(Controller1.ButtonB.pressing() && Mag < 1){
      Mag = FullMag;
      reMessage = false;
      Controller1.Screen.clearScreen();
    }

    MotorA.setVelocity(a, percent);
    MotorB.setVelocity(b, percent);
    MotorC.setVelocity(c, percent);
    MotorD.setVelocity(d, percent);

    if (fireing == true && canFire == true){
      canFire = false;
      Fire();
      Reload();
      canFire = true;
      fireing = false;
    }else{
      return;
    }

    if (Mag < 1 && reMessage == false){
      Controller1.Screen.newLine();
      Controller1.Screen.print("No More Bullets!!!");
      Controller1.Screen.newLine();
      Controller1.Screen.newLine();
      Controller1.Screen.print("Press B To Signal A Reload!");
      reMessage = true;
    }

    if (Brain.Battery.capacity() < 10){
      Controller1.Screen.newLine();
      Controller1.Screen.print("Robot Battery Low!");
    }

  }
}

void Start(){
  MotorA.spin(forward);
  MotorB.spin(forward);
  MotorC.spin(forward);
  MotorD.spin(forward);
  Controller1.ButtonA.pressed(Launch);
  Run();
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Start();
}

