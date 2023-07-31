#include "Robot.h"
#include <iostream>

#include "PPM/PPMFlipsky.h"

// setup two motors (left side of the drivebase) on DIO channels 0 and 1

PPMFlipsky leftMotor1(0);
PPMFlipsky leftMotor2(1);

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  // we have to enable them because the DIO doesn't work like normal motor controllers, and will run it even when disabled... which is bad
  leftMotor1.enable();
  leftMotor2.enable();
}

void Robot::TeleopPeriodic() {
  double joystickYValue = driverJoystick.GetY();
  double power = std::abs(joystickYValue) > 0.1 ? joystickYValue : 0;
  leftMotor1.set(power);
  leftMotor2.set(power);
}

void Robot::DisabledInit() {
  leftMotor1.disable();
  leftMotor2.disable();
}

void Robot::DisabledPeriodic() {}
void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
