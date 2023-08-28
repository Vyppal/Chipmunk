#include "Drivetrain.h"

class TankDrivebase {
  public:
    TankDrivebase(Drivetrain &drivetrain) : _drivetrain(drivetrain) {}
  
    // void onAttach() override {
    //   // nothing to do
    // }

    // void onUpdate() override {
      
    // }
  private:
    Drivetrain &_drivetrain;

    
  double _halvedWheelDistance = 0.55;

  double driveDeadzone = 0.05;
  double twistDeadzone = 0.01;

  double maxForwardSpeed = 2.23 * 0.66; // * 0.66 for children safety factor
  double maxRotationSpeed = 1.7;

  double accelerationPerTick = maxForwardSpeed / 50;

  double rightMotorSpeed = 0;
  double leftMotorSpeed = 0;
};