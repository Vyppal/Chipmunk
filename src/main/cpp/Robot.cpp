#include "Robot.h"
#include <iostream>



// setup two motors (left side of the drivebase) on DIO channels 0 and 1


static units::second_t lastPeriodic;

void Robot::RobotInit() {
  lastPeriodic = wom::now();
  _tankDrive = new TankDrivebase(&_map.tankConfig, &_map.controllers.primary);
  _elevator = new ElevatorLift(&_map.elevatorConfig, &_map.controllers.primary);
}
void Robot::RobotPeriodic() {
  auto dt = wom::now() - lastPeriodic;
  lastPeriodic = wom::now();
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  auto dt = wom::now() - lastPeriodic;
  lastPeriodic = wom::now();
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
