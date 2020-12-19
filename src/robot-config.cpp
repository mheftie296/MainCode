#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotor = motor(PORT16, ratio18_1, true);
motor rightMotor = motor(PORT17, ratio18_1, false);
motor backLeftMotor = motor(PORT10, ratio18_1, true);
motor backRightMotor = motor(PORT15, ratio18_1, false);
motor leftIntakeMotor = motor(PORT3, ratio18_1, false);
motor rightIntakeMotor = motor(PORT5, ratio18_1, false);
motor botomRoller = motor(PORT7, ratio18_1, false);
motor topMotor = motor(PORT9, ratio18_1, false);
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
line LineTrackerC = line(Brain.ThreeWirePort.C);
pot PotentiometerB = pot(Brain.ThreeWirePort.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}