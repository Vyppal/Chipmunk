#include "Robot.h"
#include <iostream>

#include "CAN_VESC.h"

CAN_VESC *m;

void Robot::RobotInit() {
  std::cout << "Starting CAN Motor control" << std::endl;
  m = new CAN_VESC(14);
}
void Robot::RobotPeriodic() {
  std::cout << "Position: " << m->get_position() << std::endl;
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
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
