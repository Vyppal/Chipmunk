#pragma once

#include <iostream>

#include <frc/Joystick.h>
#include <frc/Servo.h>

#include "motorcontrol/MotorController.h"
#include "motorcontrol/PPMFlipsky.h"

#include "TankDrive.h"
#include "ElevatorLift.h"

#include <units/length.h>
#include <units/time.h>
#include <units/voltage.h>

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
    0.4,
    0_m,
    0_m,
    {
      "",
      1_V / 1_m,          // p
      0_V / 1_m / 1_s,    // i
      0_V / 1_m * 1_s,    // d
      0_m,                // stable threshold
      0_m / 1_s,          // stable derivative threshold
      0_m                 // integral zone
    }
  };
};