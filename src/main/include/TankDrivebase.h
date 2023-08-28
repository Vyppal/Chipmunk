#include "Drivetrain.h"

class TankDrivebase {
 public:
  TankDrivebase(Drivetrain &drivetrain) : _drivetrain(drivetrain) {}
  
    // void onAttach() override {
    //   // nothing to do
    // }

      // void onUpdate() override {

      // }
  void TankDrivebase::UpdateSpeeds() {
    double joystickYValue = _joystick->GetY();
    double twistValue = _joystick->GetTwist();

    joystickYValue = std::abs(joystickYValue) > driveDeadzone ? joystickYValue : 0;
    twistValue = std::abs(twistValue) > twistDeadzone ? -twistValue : 0;

    double leftWheelVelocity = joystickYValue*maxForwardSpeed + _halvedWheelDistance * twistValue*maxRotationSpeed;
    double rightWheelVelocity = -(joystickYValue*maxForwardSpeed - _halvedWheelDistance * twistValue*maxRotationSpeed);

    double maxLeftRequested = leftWheelVelocity / maxMotorSpeed; 
    double maxRightRequested = rightWheelVelocity / maxMotorSpeed;

    if (maxLeftRequested > abs(leftMotorSpeed)) {
      int leftSign = leftMotorSpeed != 0 ? leftMotorSpeed/abs(leftMotorSpeed) : (leftWheelVelocity != 0 ? leftWheelVelocity / abs(leftWheelVelocity) : 1);
      int rightSign = rightMotorSpeed != 0 ? rightMotorSpeed/abs(rightMotorSpeed) : (rightWheelVelocity != 0 ? rightWheelVelocity / abs(rightWheelVelocity) : 1);
      leftMotorSpeed = leftSign * std::max(0, std::min(accelerationPerTick + abs(leftMotorSpeed), abs(maxLeftRequested)));
      rightMotorSpeed = rightSign * std::max(0, std::min(accelerationPerTick + abs(rightMotorSpeed), abs(maxRightRequested)));
    }
    else {
      leftMotorSpeed = leftWheelVelocity;
      rightMotorSpeed = rightWheelVelocity;
    }

    _drivetrain.set(leftMotorSpeed / maxMotorSpeed, rightMotorSpeed / maxMotorSpeed)
  }

  void TankDrivebase::Halt() {
    _drivetrain.set(0, 0);
  }

  private:
    Drivetrain &_drivetrain;

    
  double _halvedWheelDistance = 0.64;

  double driveDeadzone = 0.05;
  double twistDeadzone = 0.01;

  double maxForwardSpeed = 2.23 * 0.66; // * 0.66 for children safety factor
  double maxRotationSpeed = 1.7;

  double accelerationPerTick = maxForwardSpeed / 50;

  double rightMotorSpeed = 0;
  double leftMotorSpeed = 0;
};