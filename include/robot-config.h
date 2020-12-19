using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor leftMotor;
extern motor rightMotor;
extern motor backLeftMotor;
extern motor backRightMotor;
extern motor leftIntakeMotor;
extern motor rightIntakeMotor;
extern motor botomRoller;
extern motor topMotor;
extern controller Controller1;
extern controller Controller2;
extern line LineTrackerC;
extern pot PotentiometerB;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );