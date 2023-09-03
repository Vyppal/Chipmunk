#include "Drivetrain.h"

class TankDrivebase {
 public:
  TankDrivebase(Drivetrain &drivetrain);
  
    // void onAttach() override {
    //   // nothing to do
    // }

    // void onUpdate() override {

    // }
    void UpdateSpeeds(double joystickYValue, double joystickTwistValue);
    void Halt();
  private:
    Drivetrain &_drivetrain;

    double _halvedWheelDistance = 0.32; // was 0.64

    double driveDeadzone = 0.05;
    double twistDeadzone = 0.01;

    double maxForwardSpeed = 2.23 * 0.66; // * 0.66 for children safety factor
    double maxRotationSpeed = 1.7;

    double accelerationPerTick = maxForwardSpeed / 50;

    double rightMotorSpeed = 0;
    double leftMotorSpeed = 0;

    double maxMotorSpeed = maxForwardSpeed + _halvedWheelDistance * maxRotationSpeed;
};