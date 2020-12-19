/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\matth                                            */
/*    Created:      Tue Dec 08 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"
#include <sstream>
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         16              
// rightMotor           motor         17              
// backLeftMotor        motor         10              
// backRightMotor       motor         15              
// leftIntakeMotor      motor         3               
// rightIntakeMotor     motor         5               
// botomRoller          motor         7               
// topMotor             motor         9               
// Controller1          controller                    
// Controller2          controller                    
// LineTrackerC         line          C               
// PotentiometerB       pot           B               
// ---- END VEXCODE CONFIGURED DEVICES ----
// DIRECTIONS
// forward = 0
// right = 1
// reverse = 2
// left = 3
// turn right = 9
// turn left = 10    can be any number, but I use 10. this might change
bool shouldRollersSpin = false;
bool shouldIntakeSpin = false;

//turning
float accR = 5; //acceleration value for rotation, does not correlate to a known acceleration amount (like inches/second squared)
float cutoffR = 10;  //the value that the motors start and end the move at for rotation, should not change distance driven. must be higher than 0

//driving straight
float acc = 20; //acceleration value, does not correlate to a known acceleration amount (like inches/second squared)
float cutoff = 5; //the value that the motors start and end the move at, should not change distance driven. must be higher than 0

using namespace vex;
void pre_auton(void) {
  vexcodeInit();
  leftMotor.setMaxTorque(100, percent);   //makes sure the motors run at full speed when I tell them to spin
  rightMotor.setMaxTorque(100, percent);
  backLeftMotor.setMaxTorque(100, percent);
  backRightMotor.setMaxTorque(100, percent);
  leftIntakeMotor.setBrake(hold);
  rightIntakeMotor.setBrake(hold);
  topMotor.setVelocity(100,percent);
  botomRoller.setVelocity(100, percent);      //more important because I just tell these to spin and not the speed to spin
  leftIntakeMotor.setVelocity(100,percent);
  rightIntakeMotor.setVelocity(100, percent);
  leftMotor.spin(forward);                    //tells the drive motors to run so the bot can move
  rightMotor.spin(forward);
  backRightMotor.spin(forward);
  backLeftMotor.spin(forward);
}

float getAvMotorPos(int direction){ //returns the average degrees turned in a certan direction, multiply this value by pi, square root of 2, and 1/365 to get inches driven
  if(direction == 0) //forwards
  return (-leftMotor.position(degrees) - rightMotor.position(degrees) - backLeftMotor.position(degrees) - backRightMotor.position(degrees))/4;
  else if(direction == 1) //right
  return (-leftMotor.position(degrees) + rightMotor.position(degrees) + backLeftMotor.position(degrees) - backRightMotor.position(degrees))/4;
  else if(direction == 2) //reverse
  return (leftMotor.position(degrees) + rightMotor.position(degrees) + backLeftMotor.position(degrees) + backRightMotor.position(degrees))/4;
  else if(direction == 3) //left
  return (leftMotor.position(degrees) - rightMotor.position(degrees) - backLeftMotor.position(degrees) + backRightMotor.position(degrees))/4;
  else if(direction == 9) //turn right
  return (-leftMotor.position(degrees) + rightMotor.position(degrees) - backLeftMotor.position(degrees) + backRightMotor.position(degrees))/4;
                    //turn left
  
  return (leftMotor.position(degrees) - rightMotor.position(degrees) + backLeftMotor.position(degrees) - backRightMotor.position(degrees))/4;
}

void resetMotorPositions(){  //resets the current motor rotation returned by the integrated encoders
  leftMotor.resetPosition();
  rightMotor.resetPosition();
  backLeftMotor.resetPosition();
  backRightMotor.resetPosition();
}

void stopMotors(){                   //stops the motors, used in auton
  leftMotor.setVelocity(0,percent);
  rightMotor.setVelocity(0,percent);
  backLeftMotor.setVelocity(0,percent);
  backRightMotor.setVelocity(0,percent);
}


void turnSmooth(int distance){ //turns the specified rotation in degrees
  resetMotorPositions();
  float startR = getAvMotorPos(9);
  if(distance < 0){
    distance = -distance;
    distance *= 16.5 * 0.00860710316; // diameter * 0.00860710316, change diameter to fix not turning the specified amount
    while(distance > ((-getAvMotorPos(9) + startR) * 0.034428412)){ // while the robot has not turned the right amount
      float disR = (-(getAvMotorPos(9) + startR) * 0.034428412);
      /*
    printf("Turning");
    printf("target distance = %d\n",distance);
    printf("have gone %d of target distance\n",(int)disR);
    printf("because of that, my motor speed is %d\n",(int)(-abs((accR * disR - ((distance * accR)/2.0))+((distance * accR)/2.0)+cutoffR)));
    printf("have a good winter break!\n");
    */
      leftMotor.setVelocity((-abs(accR * disR - ((distance * accR)/2.0))+((distance * accR)/2.0)+cutoffR), percent);
      rightMotor.setVelocity(-(-abs(accR * disR - ((distance * accR)/2.0))+((distance * accR)/2.0)+cutoffR),percent);
      backLeftMotor.setVelocity((-abs(accR * disR - ((distance * accR)/2.0))+((distance * accR)/2.0)+cutoffR),percent);
      backRightMotor.setVelocity(-(-abs(accR * disR - ((distance * accR)/2.0))+((distance * accR)/2.0)+cutoffR),percent);
  }
  }
  if(distance > 0){
    distance *= 16.5 * 0.00860710316;
    while(distance > abs((getAvMotorPos(9) - startR) * 0.034428412)){
      float disR = ((getAvMotorPos(9) - startR) * 0.034428412);
      /*
      printf("Turning");
    printf("target distance = %d\n",distance);
    printf("have gone %d of target distance\n",(int)disR);
    printf("because of that, my motor speed is %d\n",(int)(-abs((accR * disR - ((distance * accR)/2.0))+((distance * accR)/2.0)+cutoffR)));
    printf("have a good winter break!\n");
    */
      leftMotor.setVelocity(-(-abs(accR * disR - ((distance * accR)/2.0))+((distance * accR)/2.0)+cutoffR), percent);
      rightMotor.setVelocity((-abs(accR * disR - ((distance * accR)/2.0))+((distance * accR)/2.0)+cutoffR),percent);
      backLeftMotor.setVelocity(-(-abs(accR * disR - ((distance * accR)/2.0))+((distance * accR)/2.0)+cutoffR),percent);
      backRightMotor.setVelocity((-abs(accR * disR - ((distance * accR)/2.0))+((distance * accR)/2.0)+cutoffR),percent);
  }
  }
  stopMotors();
}

void driveSmooth(int distance, int direction){ //drives the specified amount in inches
  resetMotorPositions();
  float start = getAvMotorPos(direction);
  while(distance > ((getAvMotorPos(direction) - start) * 0.048689127)){
    float dis = ((getAvMotorPos(direction) - start) * 0.048689127);
    /*
    printf("Direction = %d\n",direction);
    printf("target distance = %d\n",distance);
    printf("have gone %d of target distance\n",(int)dis);
    printf("because of that, my motor speed is %d\n",(int)(-abs((acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff)));
    printf("have a good winter break!\n");
    */    //if ur having problems uncomment this and run the code with the controller connected to the computer
    if(direction == 0){
      leftMotor.setVelocity(-(-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff), percent);
      rightMotor.setVelocity(-(-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
      backLeftMotor.setVelocity(-(-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
      backRightMotor.setVelocity(-(-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
    }
    if(direction == 1){ 
      leftMotor.setVelocity(-(-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff), percent);
      rightMotor.setVelocity((-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
      backLeftMotor.setVelocity((-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
      backRightMotor.setVelocity(-(-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
    }
    if(direction == 2){
      leftMotor.setVelocity((-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff), percent);
      rightMotor.setVelocity((-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
      backLeftMotor.setVelocity((-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
      backRightMotor.setVelocity((-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
    }
    if(direction == 3){
      leftMotor.setVelocity((-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff), percent);
      rightMotor.setVelocity(-(-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
      backLeftMotor.setVelocity(-(-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
      backRightMotor.setVelocity((-abs(acc * dis - ((distance * acc)/2.0))+((distance * acc)/2.0)+cutoff),percent);
    }
  }
  stopMotors();
}

void autonomous(void) {
    stopMotors();       //needs to be at the top of autonomous
    turnSmooth(360);
    turnSmooth(-360);
    driveSmooth(10, 3);
    topMotor.spin(reverse);         //runs the cycler
    botomRoller.rotateFor(forward, 5000, msec);   //this works as a wait
    topMotor.stop();

}

void usercontrol(void) {
  while (1) {
    leftMotor.setVelocity((-Controller1.Axis3.value() - Controller1.Axis1.value() - Controller1.Axis4.value())/1.27,percent);    //driver control
    rightMotor.setVelocity((-Controller1.Axis3.value() + Controller1.Axis1.value() + Controller1.Axis4.value())/1.27,percent);    //of the drive
    backLeftMotor.setVelocity((-Controller1.Axis3.value() - Controller1.Axis1.value() + Controller1.Axis4.value())/1.27,percent);
    backRightMotor.setVelocity((-Controller1.Axis3.value() + Controller1.Axis1.value() - Controller1.Axis4.value())/1.27,percent);
    Brain.Screen.setCursor(5, 5);               //uncomment both lines
    Brain.Screen.print(PotentiometerB.value(degrees));      //used for debugging a value
    wait(20, msec);
    if(Controller2.ButtonL2.pressing()){ //intakes in
      leftIntakeMotor.spin(forward);
      rightIntakeMotor.spin(reverse);
      shouldIntakeSpin = true;
    }
    else if(Controller2.ButtonL1.pressing()){ //intakes out
      leftIntakeMotor.spin(reverse);
      rightIntakeMotor.spin(forward);
      shouldIntakeSpin = true;
    } else {
       if(shouldIntakeSpin){  //stopping the intakes
        shouldIntakeSpin = false;
        leftIntakeMotor.stop();
        rightIntakeMotor.stop();
      }
    }
    if(Controller2.ButtonR2.pressing()){ //cycle normal
      botomRoller.spin(forward);
      topMotor.spin(reverse);
      shouldRollersSpin = true;
    }
    else if(Controller2.ButtonR1.pressing()){ //cycle out back
      botomRoller.spin(forward);
      topMotor.spin(forward);
      shouldRollersSpin = true;
    } else {
      if(shouldRollersSpin){  //stopping rollers
        shouldRollersSpin = false;
        botomRoller.stop();
        topMotor.stop();
        
      }
    }
  }
}



int main() {
  pre_auton();
  competition().autonomous(autonomous); //runs autonomous in a competition
  //autonomous();                         //runs autonomous when the program is ran
  competition().drivercontrol(usercontrol);
  usercontrol();
  
}

