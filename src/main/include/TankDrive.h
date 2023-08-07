#pragma once

#include "PPM/PPMFlipsky.h"
#include <frc/Joystick.h>

#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/angular_velocity.h>

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
  void Halt();


 private:
  TankConfig *_config;
  frc::Joystick *_joystick;

  double _halvedWheelDistance;

  double driveDeadzone = 0.05;
  double twistDeadzone = 0.01;

  double maxForwardSpeed = 2.23;
  double maxRotationSpeed = 1.7;

  double maxMotorSpeed = maxForwardSpeed + _halvedWheelDistance * maxRotationSpeed;
};