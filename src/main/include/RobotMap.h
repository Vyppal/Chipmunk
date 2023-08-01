#pragma once

#include <iostream>

#include <frc/Joystick.h>
#include <frc/Servo.h>


#include "PPM/PPMFlipsky.h"


struct RobotMap {
  struct Controllers {
    frc::Joystick primary{0};
  };
  struct Drivebase {
    struct Left {
      PPMFlipsky front{0, 10_kHz};
      PPMFlipsky back{1, 10_kHz};
    } left;
    struct Right {
      PPMFlipsky front{2, 10_kHz};
      PPMFlipsky back{3, 10_kHz};
    } right;
  } drivebase;
  struct HoldingFlaps {
    frc::Servo left{4};
    frc::Servo right{5};
  } holdingFlaps;

  PPMFlipsky elevatorMotor{4, 10_kHz};

  Controllers controller;
  Drivebase drivebase;
  HoldingFlaps holdingFlaps;
};