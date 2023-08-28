#include "TankDrive.h"

TankDrivebase::TankDrivebase(TankConfig *tankConfig, frc::Joystick *joystick) : _config(tankConfig), _joystick(joystick) {
  _halvedWheelDistance = tankConfig->trackWidth / 2;
}


void TankDrivebase::UpdateSpeeds() {
  double joystickYValue = _joystick->GetY();
  double twistValue = _joystick->GetTwist();
  
  joystickYValue = std::abs(joystickYValue) > driveDeadzone ? joystickYValue : 0;
  twistValue = std::abs(twistValue) > twistDeadzone ? -twistValue : 0;

  double forwardSpeed = joystickYValue * maxForwardSpeed;
  if (forwardSpeed < 0.05) {maxRotationSpeed = 36; } else {maxRotationSpeed = 24;}
  
  double rotationSpeed = twistValue * maxRotationSpeed;


  double leftWheelVelocity = forwardSpeed + _halvedWheelDistance * rotationSpeed;
  double rightWheelVelocity = -(forwardSpeed - _halvedWheelDistance * rotationSpeed);

  double maxLeftRequested = leftWheelVelocity / maxMotorSpeed; 
  double maxRightRequested = rightWheelVelocity / maxMotorSpeed;

  // if (maxLeftRequested > abs(leftMotorSpeed)) {
  //   int leftSign = leftMotorSpeed != 0 ? leftMotorSpeed/abs(leftMotorSpeed) : (leftWheelVelocity != 0 ? leftWheelVelocity / abs(leftWheelVelocity) : 1);
  //   int rightSign = rightMotorSpeed != 0 ? rightMotorSpeed/abs(rightMotorSpeed) : (rightWheelVelocity != 0 ? rightWheelVelocity / abs(rightWheelVelocity) : 1);
  //   leftMotorSpeed = leftSign * std::max(0, std::min(accelerationPerTick + abs(leftMotorSpeed), abs(maxLeftRequested)));
  //   rightMotorSpeed = rightSign * std::max(0, std::min(accelerationPerTick + abs(rightMotorSpeed), abs(maxRightRequested)));
  // }
  // else {
  //   leftMotorSpeed = leftWheelVelocity / maxMotorSpeed;
  //   rightMotorSpeed = rightWheelVelocity / maxMotorSpeed; 
  // }
  
  _config->leftFront.set(leftWheelVelocity / maxMotorSpeed / 3);
  _config->leftBack.set(leftWheelVelocity / maxMotorSpeed / 3);
  _config->rightFront.set(-rightWheelVelocity / maxMotorSpeed / 3);
  _config->rightBack.set(-rightWheelVelocity / maxMotorSpeed / 3);

}

void TankDrivebase::Halt() {
  _config->leftFront.set(0);
  _config->leftBack.set(0);
  _config->rightFront.set(0);
  _config->rightBack.set(0);
}