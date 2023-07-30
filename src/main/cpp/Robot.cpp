#include <fmt/core.h>

#include "Robot.h"

#include "FlipskyController.h"

#include <iostream>


// Flipsky leftMotor1{0, true};
// Flipsky leftMotor2{1, true};
// Flipsky rightMotor1{2, true};
// Flipsky rightMotor2{3, true};

frc::PWM leftMotor1{0};
frc::PWM leftMotor2{1};
frc::PWM rightMotor1{2};
frc::PWM rightMotor2{3};

int freq = 1500;
bool forward = true;



void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}
void Robot::TeleopInit() {
  rightMotor1.SetBounds(2, 0.2, 0, -0.2, -2);
}

void Robot::TeleopPeriodic() {
  double joystickYValue = driverJoystick.GetX();

  if (abs(joystickYValue) <= driveDeadzone) {   joystickYValue = 0;  freq = 1500; }
  else if (joystickYValue > 0) {
    freq = 2000;
  }
  else {
    freq = 1000;
  }
  // if (abs(twistValue) <= twistDeadzone) {   twistValue = 0;   }

  // double forwardSpeed = joystickXValue * maxForwardSpeed;
  // double rotationSpeed = twistValue * maxRotationSpeed;


  // double leftWheelVelocity = forwardSpeed + distanceBetweenWheels/2 * rotationSpeed;
  // double rightWheelVelocity = forwardSpeed - distanceBetweenWheels/2 * rotationSpeed;


  // if (forward) {
  //   freq += 0.001; // increment position by 0.1%
  //   if (freq >= 1.0) {
  //     forward = false;
  //   }
  // } else {
  //   freq -= 0.001; // decrement position by 0.1%
  //   if (freq <= 0.0) {
  //     forward = true;
  //   }
  // }
  
  rightMotor1.SetSpeed(joystickYValue);
  // leftMotor1.SetSpeed(joystickYValue); // set the new PWM position
  // leftMotor2.SetSpeed(joystickYValue);
  // rightMotor1.SetSpeed(joystickYValue);
  // rightMotor2.SetSpeed(joystickYValue);
  std::cout << "    Joystick Val: " << joystickYValue << std::endl;
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
