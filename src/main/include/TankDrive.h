#pragma once

#include "PPM/PPMFlipsky.h"
#include <frc/XboxController.h>

#include <units/length.h>
#include <units/time.h>

struct TankConfig {
  PPMFlipsky leftFront;
  PPMFlipsky leftBack;
  PPMFlipsky rightFront;
  PPMFlipsky rightBack;
  double trackWidth;
};


class TankDrivebase {
 public:
  TankDrivebase(TankConfig *tankConfig, frc::XboxController *controller);
  void UpdateSpeeds();
  void UpdateSpeedsJoystick();
  void UpdateSpeedsXbox_V1();
  void UpdateSpeedsXbox_V2();
  
  void lowerSpeed() {
    maxForwardSpeed = 1;
    maxRotationSpeed = 1.1;
  }
  void higherSpeed() {
    maxForwardSpeed = 2.23;
    maxRotationSpeed = 2.4;
  }
  void normalSpeed() {
    maxForwardSpeed = 1.5;
    maxRotationSpeed = 1.61;
  }


 private:
  TankConfig *_config;
  frc::XboxController *_controller;

  double _halvedWheelDistance;

  double driveDeadzone = 0.05;
  double twistDeadzone = 0.01;

  double maxForwardSpeed = 1; // in meters per second
  double maxRotationSpeed = 1.4; // at this point, this is unitless i swear

  double maxMotorSpeed = maxForwardSpeed + _halvedWheelDistance * maxRotationSpeed;
};