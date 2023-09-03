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

#include "ElevatorLift.h"


struct RobotMap {
  struct Controllers {
    frc::Joystick driver{0};
  } controllers;
  struct Drivebase {
    Gearbox left{"Left Gearbox", {PPMFlipsky(9), PPMFlipsky(1)}};
    Gearbox right{"Right Gearbox", {PPMFlipsky(8), PPMFlipsky(0)}};  
    Drivetrain drivetrain{left, right};
  } drivebase;
  ElevatorConfig elevatorConfig {
  Gearbox{"Elevator Gearbox", {PPMFlipsky(5)}},
  0,
  0.43,
  PIDController{0, 0, 0}
};
} robotMap;