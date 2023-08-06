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
  // struct TankConfiguration {
  //   PPMFlipsky leftFront{0};
  //   PPMFlipsky leftBack{1};
  //   PPMFlipsky rightFront{2};
  //   PPMFlipsky rightBack{3};
  //   int wheelDist = 0.64; // distance between wheel sides

  //   // LeftMotors {
  //   //   PPMFlipsky front{0};
  //   //   PPMFlipsky back{1};
  //   // }; LeftMotors leftMotors;
  //   // RightMotors {
  //   //   PPMFlipsky front{2};
  //   //   PPMFlipsky back{3};
  //   // }; RightMotors rightMotors;
    
  //   TankConfig {
  //     leftFront,
  //     leftBack,
  //     rightFront,
  //     rightBack,
  //     wheelDist
  //   };
  // };
  // TankConfiguration tankConfig;

  TankConfig tankConfig{
    PPMFlipsky{0},
    PPMFlipsky{1},
    PPMFlipsky{2},
    PPMFlipsky{3},
    0.64
  };
  PPMFlipsky elevatorMotor{4};
};