#include "Robot.h"
#include <iostream>

void Robot::RobotInit() {
  _tankDrive = new TankDrivebase(&_map.tankConfig, &_map.controllers.primary);
  _elevator = new ElevatorLift(&_map.elevatorConfig, &_map.controllers.primary);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  _tankDrive->UpdateSpeeds();
}

void Robot::DisabledInit() {
  _tankDrive->Halt();
}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
