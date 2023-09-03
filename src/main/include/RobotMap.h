#pragma once

#include <iostream>

#include <frc/Joystick.h>
#include <frc/Servo.h>

#include "motorcontrol/MotorController.h"
#include "motorcontrol/PPMFlipsky.h"

#include "Gearbox.h"
#include "Drivetrain.h"

#include <units/length.h>
#include <units/time.h>
#include <units/voltage.h>

struct RobotMap {
  struct Controllers {
    frc::Joystick driver{0};
  } controllers;
  struct Drivebase {
    Gearbox left{Gearbox("Left Gearbox", {PPMFlipsky(9), PPMFlipsky(1)})};
    Gearbox right{Gearbox("Right Gearbox", {PPMFlipsky(8), PPMFlipsky(0)})};
    // Gearbox left = Gearbox{"Left Gearbox", lefts};
    // Gearbox right = Gearbox{"Right Gearbox", rights};
  
    Drivetrain drivetrain{left, right};
  } drivebase;
} robotMap;