#pragma once

#include "PPM/PPMFlipsky.h"
#include <frc/Joystick.h>

#include <units/length.h>
#include <units/time.h>

// struct LeftMotors {
//   PPMFlipsky front;
//   PPMFlipsky back;
// };

// struct RightMotors {
//   PPMFlipsky front;
//   PPMFlipsky back;
// };

struct TankConfig {
  PPMFlipsky leftFront;
  PPMFlipsky leftBack;
  PPMFlipsky rightFront;
  PPMFlipsky rightBack;
  double trackWidth;
};


class TankDrivebase {
 public:
  TankDrivebase(TankConfig *tankConfig, frc::Joystick *joystick);
  void UpdateSpeeds();


 private:
  TankConfig *_config;
  frc::Joystick *_joystick;

  double _halvedWheelDistance;

  double driveDeadzone = 0.05;
  double twistDeadzone = 0.01;

  double maxForwardSpeed = 2.23;//_m / 1_s; // in meters per second
  // double maxRotationSpeed = 1.7;
  double maxRotationSpeed = 2.4;

  double maxMotorSpeed = maxForwardSpeed + _halvedWheelDistance * maxRotationSpeed;
};