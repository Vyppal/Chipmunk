#include "Robot.h"
#include <iostream>

#include <frc/XboxController.h>

void Robot::RobotInit() {
  std::cout << "RobotInit" << std::endl;
  _tankDrivebase = new TankDrivebase(_robotMap.drivebase.drivetrain);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  // _tankDrivebase->update();
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
