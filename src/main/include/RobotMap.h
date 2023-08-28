#pragma once

#include <iostream>

#include <frc/Joystick.h>
#include <frc/Servo.h>

#include "motorcontrol/MotorController.h"
#include "motorcontrol/PPMFlipsky.h"

#include "Gearbox.h"

#include <units/length.h>
#include <units/time.h>
#include <units/voltage.h>

struct RobotMap {
  struct Drivebase {
    Gearbox left{Gearbox("Left Gearbox", {PPMFlipsky(9), PPMFlipsky(1)})};
    Gearbox right{Gearbox("Right Gearbox", {PPMFlipsky(8), PPMFlipsky(0)})};
  
    Drivetrain drivetrain{left, right};
  } drivebase;
};