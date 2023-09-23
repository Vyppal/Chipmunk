#pragma once

#include <iostream>

#include <frc/Joystick.h>
#include <frc/Servo.h>

#include "PPM/PPMFlipsky.h"

#include "TankDrive.h"

#include <units/length.h>
#include <units/time.h>

struct RobotMap {
  struct Controllers {
    frc::Joystick primary{0};
  };
  Controllers controllers;
  TankConfig tankConfig{
    PPMFlipsky{1},
    PPMFlipsky{9},
    PPMFlipsky{0},
    PPMFlipsky{8},
    0.64
  };
  PPMFlipsky elevatorMotor{5};
};