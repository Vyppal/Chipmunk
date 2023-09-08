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
  
  if (_robotMap->controllers.driver.GetRawButton(1)) {  elevatorDirectionHandler.push_back(1);  }
  else {  elevatorDirectionHandler.erase(remove_if(elevatorDirectionHandler.begin(),elevatorDirectionHandler.end(),rmv::remove(1)),elevatorDirectionHandler.end());  }
  if (_robotMap->controllers.driver.GetRawButton(2)) {  elevatorDirectionHandler.push_back(-1);  }
  else {  elevatorDirectionHandler.erase(remove_if(elevatorDirectionHandler.begin(),elevatorDirectionHandler.end(),rmv::remove(-1)),elevatorDirectionHandler.end());  }

  _elevator->onUpdate(dt, _robotMap->controllers.driver.GetZ(), elevatorDirectionHandler.back());

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
