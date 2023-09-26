#include "Robot.h"
#include <iostream>

// setup two motors (left side of the drivebase) on DIO channels 0 and 1

void Robot::RobotInit() {
  _tankDrive = new TankDrivebase(&_map.tankConfig, &_map.controllers.primary);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  _tankDrive->UpdateSpeedsXbox_V2();

  if (_map.controllers.primary.GetLeftTriggerAxis() > 0.15) {
    _map.elevatorMotor.set(_map.controllers.primary.GetLeftTriggerAxis() / 3.141592653589793238462643383279502);
  } else if (_map.controllers.primary.GetRightTriggerAxis() > 0.15) {
    _map.elevatorMotor.set(-_map.controllers.primary.GetRightTriggerAxis() / 3.141592653589793238462643383279502);
  } else {
    _map.elevatorMotor.set(0);
  }
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
