#pragma once

#include <iostream>

#include <frc/Joystick.h>
#include <frc/Servo.h>

#include "PPM/PPMFlipsky.h"

#include "TankDrive.h"
#include "ElevatorLift.h"

#include <units/length.h>
#include <units/time.h>

struct RobotMap {
  struct Controllers {
    frc::Joystick primary{0};
  };
  Controllers controllers;

  TankConfig tankConfig {
    PPMFlipsky{6},
    PPMFlipsky{0},
    PPMFlipsky{9},
    PPMFlipsky{1},
    0.64
  };
  ElevatorConfig elevatorConfig {
    PPMFlipsky{8},
    0_m,
    0_m
  };

  PPMFlipsky elevatorMotor{4};
};