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
  if (_map.controllers.primary.GetTrigger()) {
    if (fabs(_map.controllers.primary.GetThrottle()) > 0.15) {
      if (_map.controllers.primary.GetThrottle() > 0) {
        posTimer = posTimer + 0.02;
        // negTimer = 0;
        if (posTimer < 5) {
          _map.elevatorMotor.set(_map.controllers.primary.GetThrottle() / 3.141592653589793238462643383);
        } else {
          _map.elevatorMotor.set(0);
        }
      } else {
        // posTimer = 0;
        negTimer += 0.02;
        if (negTimer < 5) {
          _map.elevatorMotor.set(_map.controllers.primary.GetThrottle() / 3.141592653589793238462643383);
        } else {
          _map.elevatorMotor.set(0);
        }
      }
    } else {
      _map.elevatorMotor.set(0);
    }
  }
  else {
    _map.elevatorMotor.set(0);
  }
  std::cout << posTimer << " " << negTimer << std::endl;
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
