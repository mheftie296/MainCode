# MainCode
Main Vex code for 6813C Turning Point

For autonomous, 
driveSmooth(distance) will drive about the requested distance in inches, and turnSmooth(degrees) will turn the requested distance in degrees.
There are values at the top of the code to change the acceleration speed and the speed the robot starts and ends the movements at for both rotation and driving.

if the robot is not behaving as expected during autonomous, there is commented out print statements inside driveSmooth and turnSmooth that will print to the console in vexcode if the controller is connected to the computer when autonomous is running.

for running the autonomous when a match runs, uncomment `competition().autonomous(autonomous);` at the bottom of the code. 
for running the autonomous whenever the code runs, uncomment `autonomous();`

driveSmooth will (probably) not drive with negative numbers, use 0 for direction to drive forwards, 1 to strafe left, 2 to drive backwards, and 3 to strafe left

turnSmooth will work with negative increments corresponding to counterclockwise

you can run the intakes or cycler like this
```
leftIntakeMotor.spin(forward);
leftIntakeMotor.spin(reverse);
wait(1000,msec);
leftIntakeMotor.stop();
rightIntakeMotor.stop();
```
or run them while moving like this
```
leftIntakeMotor.spin(forward);
leftIntakeMotor.spin(reverse);
driveSmooth(10,2);
leftIntakeMotor.stop();
rightIntakeMotor.stop();
```
