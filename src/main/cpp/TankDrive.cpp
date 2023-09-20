#include "TankDrive.h"

TankDrivebase::TankDrivebase(TankConfig *tankConfig, frc::Joystick *joystick) : _config(tankConfig), _joystick(joystick) {
  _halvedWheelDistance = tankConfig->trackWidth / 2;
}


void TankDrivebase::UpdateSpeeds() {
  double joystickYValue = _joystick->GetY();
  double joystickTwistValue = _joystick->GetTwist();
  
  joystickYValue = std::abs(joystickYValue) > driveDeadzone ? joystickYValue : 0;
  joystickTwistValue = std::abs(joystickTwistValue) > twistDeadzone ? -joystickTwistValue : 0;

  double forwardSpeed = joystickYValue * maxForwardSpeed;
  double rotationSpeed = joystickTwistValue * maxRotationSpeed;

  double leftWheelVelocity = forwardSpeed + _halvedWheelDistance * rotationSpeed;
  double rightWheelVelocity = -(forwardSpeed - _halvedWheelDistance * rotationSpeed);

  double leftRequested = leftWheelVelocity / maxMotorSpeed; 
  double rightRequested = rightWheelVelocity / maxMotorSpeed;

  _config->leftFront.set(leftRequested);
  _config->leftBack.set(leftRequested);
  _config->rightFront.set(-rightRequested);
  _config->rightBack.set(-rightRequested);
}