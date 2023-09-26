#include "TankDrive.h"

TankDrivebase::TankDrivebase(TankConfig *tankConfig, frc::XboxController *controller) : _config(tankConfig), _controller(controller) {
  _halvedWheelDistance = tankConfig->trackWidth / 2;
}

void TankDrivebase::UpdateSpeedsJoystick() {
  // double joystickYValue = _joystick->GetY();
  // double joystickTwistValue = _joystick->GetTwist();
  
  // joystickYValue = std::abs(joystickYValue) > driveDeadzone ? joystickYValue : 0;
  // joystickTwistValue = std::abs(joystickTwistValue) > twistDeadzone ? -joystickTwistValue : 0;

  // double forwardSpeed = joystickYValue * maxForwardSpeed;
  // double rotationSpeed = joystickTwistValue * maxRotationSpeed;

  // double leftWheelVelocity = forwardSpeed + _halvedWheelDistance * rotationSpeed;
  // double rightWheelVelocity = -(forwardSpeed + _halvedWheelDistance * rotationSpeed);

  // double leftRequested = leftWheelVelocity / maxMotorSpeed; 
  // double rightRequested = rightWheelVelocity / maxMotorSpeed;

  // _config->leftFront.set(leftRequested);
  // _config->leftBack.set(leftRequested);
  // _config->rightFront.set(-rightRequested);
  // _config->rightBack.set(-rightRequested);
}

void TankDrivebase::UpdateSpeedsXbox_V2() {
  double leftYValue = _controller->GetLeftY() * 0.8;
  double rightXValue = -_controller->GetRightX();

  double forwardSpeed = maxForwardSpeed * leftYValue;
  double rotationSpeed = maxRotationSpeed * rightXValue;
  
  double leftWheelVelocity = forwardSpeed + _halvedWheelDistance * rotationSpeed;
  double rightWheelVelocity = -(forwardSpeed - _halvedWheelDistance * rotationSpeed);

  _config->leftFront.set(leftWheelVelocity / maxMotorSpeed);
  _config->leftBack.set(leftWheelVelocity / maxMotorSpeed);

  _config->rightFront.set(-rightWheelVelocity / maxMotorSpeed);
  _config->rightBack.set(-rightWheelVelocity / maxMotorSpeed);
}

void TankDrivebase::UpdateSpeedsXbox_V1() {
  double leftYValue = _controller->GetLeftY();
  leftYValue = std::abs(leftYValue) > driveDeadzone ? leftYValue : 0;
  
  double rightYValue = _controller->GetRightY();
  rightYValue = std::abs(rightYValue) > driveDeadzone ? rightYValue : 0;

  double leftRequested = maxForwardSpeed * leftYValue / maxMotorSpeed; 
  double rightRequested = maxForwardSpeed * rightYValue / maxMotorSpeed;

  _config->leftFront.set(leftRequested);
  _config->leftBack.set(leftRequested);
  _config->rightFront.set(-rightRequested);
  _config->rightBack.set(-rightRequested);
}