#include "Robot.h"
#include <iostream>


void Robot::RobotInit() {
  std::cout << "RobotInit" << std::endl;
  _robotMap = &robotMap;
  _tankDrivebase = new TankDrivebase(_robotMap->drivebase.drivetrain);
  _elevator = new ElevatorLift(&_robotMap->elevatorConfig);
  
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  currentTime = std::time(nullptr);
  int dt = (prevTime - currentTime) / 1000;
  _tankDrivebase->UpdateSpeeds(_robotMap->controllers.driver.GetY(), _robotMap->controllers.driver.GetTwist());
  if (_robotMap->controllers.driver.GetTriggerPressed()) {
    _elevator->onUpdate(dt, _robotMap->controllers.driver.GetZ());
  } else {
    _elevator->halt();
  }
  prevTime = currentTime;
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
