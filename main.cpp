/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Sydney Gabe Hodge                                         */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  excuse me sir? yes, you. your mother. adios!              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath> // allows (std::abs)

using namespace vex;

// A global instance of competition
competition Competition;
vex::controller Controller1(controllerType::primary);
vex::motor FR(vex::PORT7, ratio18_1, true);
vex::motor FL(vex::PORT9, ratio18_1, false);
vex::motor BL(vex::PORT10, ratio18_1, true);
vex::motor BR(vex::PORT5, ratio18_1, false);
vex::motor TL(vex::PORT8, ratio18_1, false);
vex::motor TR(vex::PORT19, ratio18_1, true);
vex::motor_group Drivetrain(FR, FL, BL, BR, TL, TR);
vex::motor_group Left(FL, BL, TL);
vex::motor_group Right(FR, BR, TR);
  

     ////////////////////////////////////////////
    //                                        //
   //                                        //
  //        Pre-Autonomous Functions        //
 //                                        //
//                                        //
///////////////////////////////////////////

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}




     ////////////////////////////////////////////
    //                                        //
   //                                        //
  //             Autonomous Task            //
 //                                        //
//                                        //
///////////////////////////////////////////

void autonomous(void) {
}







     ////////////////////////////////////////////
    //                                        //
   //                                        //
  //             Driver Control             //
 //                                        //
//                                        //
///////////////////////////////////////////

void usercontrol(void) {
  

//Drivetrain
double turnImportance = 0.5;

  bool reverse_drive = false;
  int reverse_lock = 0;

  //Controller Axis Code
  while (true) {
    double turnPct = Controller1.Axis4.position();
double forwardPct = Controller1.Axis2.position();

double turnVolts = turnPct * 0.12;
double forwardVolts = forwardPct * 0.12 * (1 - (std::abs(turnVolts)/12.0) * turnImportance);


  if (Controller1.ButtonA.pressing() && reverse_lock==0){
    reverse_drive = !reverse_drive;
    reverse_lock = 1;}

    else if (!Controller1.ButtonA.pressing()){
      reverse_lock = 0;}

        if (reverse_drive){
FR.spin(forward, (forwardVolts + turnVolts), voltageUnits::volt);
FL.spin(forward, (forwardVolts - turnVolts), voltageUnits::volt);
BR.spin(forward, (forwardVolts + turnVolts), voltageUnits::volt);
BL.spin(forward, (forwardVolts - turnVolts), voltageUnits::volt);
TR.spin(forward, (forwardVolts + turnVolts), voltageUnits::volt);
TL.spin(forward, (forwardVolts - turnVolts), voltageUnits::volt);
}

        else{
FR.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);
FL.spin(forward, forwardVolts + turnVolts, voltageUnits::volt);
BR.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);
BL.spin(forward, forwardVolts + turnVolts, voltageUnits::volt);
TR.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);
TL.spin(forward, forwardVolts + turnVolts, voltageUnits::volt);
}
    


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
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