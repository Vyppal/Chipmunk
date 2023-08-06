#include "TankDrive.h"

TankDrivebase::TankDrivebase(TankConfig *tankConfig, frc::Joystick *joystick) : _config(tankConfig), _joystick(joystick) {
  _halvedWheelDistance = tankConfig->trackWidth / 2;
}


void TankDrivebase::UpdateSpeeds() {
  double joystickYValue = _joystick->GetY();
  double twistValue = _joystick->GetTwist();
  
  joystickYValue = std::abs(joystickYValue) > driveDeadzone ? joystickYValue : 0;
  twistValue = std::abs(twistValue) > twistDeadzone ? twistValue : 0;

  double forwardSpeed = joystickYValue * maxForwardSpeed;
  double rotationSpeed = twistValue * maxRotationSpeed;

  double leftWheelVelocity = forwardSpeed + _halvedWheelDistance * rotationSpeed;
  double rightWheelVelocity = -(forwardSpeed - _halvedWheelDistance * rotationSpeed);

  _config->leftFront.set(leftWheelVelocity / maxMotorSpeed);
  _config->leftBack.set(leftWheelVelocity / maxMotorSpeed);
  _config->rightFront.set(rightWheelVelocity / maxMotorSpeed);
  _config->rightBack.set(rightWheelVelocity / maxMotorSpeed);
  // _config->leftBack.set(-0.4);
  // _config->leftFront.set(-0.4);
}