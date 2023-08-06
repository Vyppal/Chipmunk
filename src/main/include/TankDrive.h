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
  units::meter_t trackWidth;
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

  units::meters_per_second_t maxForwardSpeed = 2.23_m / 1_s;
  units::degrees_per_second_t maxRotationSpeed = 120_deg / 1_s;

  double maxMotorSpeed = maxForwardSpeed + _halvedWheelDistance * maxRotationSpeed;
};