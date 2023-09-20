#include "Robot.h"
#include <iostream>

void Robot::RobotInit() {
  _tankDrive = new TankDrivebase(&_map.tankConfig, &_map.controllers.primary);
  // _elevator = new ElevatorLift(&_map.elevatorConfig, &_map.controllers.primary);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  _tankDrive->UpdateSpeeds();
  if (_map.controllers.primary.GetTrigger()) {
    int moveDir = 0;
    if (fabs(_map.controllers.primary.GetThrottle()) > 0.15) {
      elevatorMotor.set(_map.controllers.primary.GetThrottle() / 5);
    }
  }
  else {
    elevatorMotor.set(0);
  }
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
