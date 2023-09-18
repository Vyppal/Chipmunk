#include "Robot.h"
#include <iostream>
#include <algorithm>
#include "CAN_VESC.h"

CAN_VESC *m;

void Robot::RobotInit() {
  std::cout << "Starting CAN Motor control" << std::endl;
  m = new CAN_VESC(14);
  std::cout << "RobotInit" << std::endl;
  _robotMap = &robotMap;
  _tankDrivebase = new TankDrivebase(_robotMap->drivebase.drivetrain);
  _elevator = new ElevatorLift(&_robotMap->elevatorConfig);
  
}
void Robot::RobotPeriodic() {
  std::cout << "Position: " << m->get_position() << std::endl;
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  currentTime = std::time(nullptr);
  int dt = (prevTime - currentTime) / 1000;
  _tankDrivebase->UpdateSpeeds(_robotMap->controllers.driver.GetY(), _robotMap->controllers.driver.GetTwist());
  
  if (_robotMap->controllers.driver.GetRawButton(1)) {  elevatorDirectionHandler.push_back(1);  }
  else {  elevatorDirectionHandler.erase(remove(elevatorDirectionHandler.begin(),elevatorDirectionHandler.end(),1),elevatorDirectionHandler.end());  }
  if (_robotMap->controllers.driver.GetRawButton(2)) {  elevatorDirectionHandler.push_back(-1);  }
  else {  elevatorDirectionHandler.erase(remove(elevatorDirectionHandler.begin(),elevatorDirectionHandler.end(),-1),elevatorDirectionHandler.end());  }

  _elevator->onUpdate(dt, _robotMap->controllers.driver.GetZ(), elevatorDirectionHandler.back());

  prevTime = currentTime;

  // m.vesc_set_duty_b(1.0);
  // m.vesc_set_duty_b(1.0);
  // std::cout << "Position: " << m.get_position() << std::endl;
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
