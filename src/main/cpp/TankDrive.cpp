#include "TankDrivebase.h"

TankDrivebase::TankDrivebase(Drivetrain &drivetrain) : _drivetrain(drivetrain) {}


void TankDrivebase::UpdateSpeeds(double joystickYValue, double joystickTwistValue) {  
  joystickYValue = std::abs(joystickYValue) > driveDeadzone ? joystickYValue : 0;
  joystickTwistValue = std::abs(joystickTwistValue) > twistDeadzone ? -joystickTwistValue : 0;

  double forwardSpeed = joystickYValue * maxForwardSpeed;
  double rotationSpeed = joystickTwistValue * maxRotationSpeed;

  double leftWheelVelocity = forwardSpeed + _halvedWheelDistance * rotationSpeed;
  double rightWheelVelocity = -(forwardSpeed - _halvedWheelDistance * rotationSpeed);

  double leftRequested = leftWheelVelocity / maxMotorSpeed; 
  double rightRequested = rightWheelVelocity / maxMotorSpeed;

  _drivetrain.set(leftRequested, rightRequested);
}

void TankDrivebase::Halt() {
  _drivetrain.set(0, 0);
}