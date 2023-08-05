#include "Robot.h"
#include <iostream>

#include "PPM/PPMFlipsky.h"

// setup two motors (left side of the drivebase) on DIO channels 0 and 1

PPMFlipsky leftMotor1(0);
PPMFlipsky leftMotor2(1);
PPMFlipsky rightMotor1(2);
PPMFlipsky rightMotor2(3);


void Robot::RobotInit() {}
void Robot::RobotPeriodic() {
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  // we have to enable them because the DIO doesn't work like normal motor controllers, and will run it even when disabled... which is bad
  leftMotor1.enable();
  // leftMotor2.enable();
  // rightMotor1.enable();
  // rightMotor2.enable();
}

void Robot::TeleopPeriodic() {
  double joystickYValue = driverJoystick.GetY();
  double twistValue = driverJoystick.GetTwist();

   if (abs(twistValue) <= twistDeadzone) {   twistValue = 0;   }

  double forwardSpeed = joystickYValue * maxForwardSpeed;
  double rotationSpeed = twistValue * maxRotationSpeed;

  double leftWheelVelocity = forwardSpeed + distanceBetweenWheels/2 * rotationSpeed;
  double rightWheelVelocity = forwardSpeed - distanceBetweenWheels/2 * rotationSpeed;  

  double power = std::abs(joystickYValue) > 0.1 ? joystickYValue : 0;

  leftMotor1.set(leftWheelVelocity / maxMotorSpeed);
  // leftMotor2.set(leftWheelVelocity / maxMotorSpeed);
  // rightMotor1.set(rightWheelVelocity / maxMotorSpeed);
  // rightMotor2.set(rightWheelVelocity / maxMotorSpeed);
}

void Robot::DisabledInit() {
  leftMotor1.disable();
  // leftMotor2.disable();
  // rightMotor1.disable();
  // rightMotor2.disable();
}

void Robot::DisabledPeriodic() {}
void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
