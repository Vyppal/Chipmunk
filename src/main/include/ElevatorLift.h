#pragma once

#include <units/length.h>
#include <units/time.h>
#include <units/voltage.h>

#include <frc/Joystick.h>

#include "ppm/PPMMotor.h"
#include "PIDController.h"
#include "Gearbox.h"

struct ElevatorConfig {
  Gearbox motor;
  // int maxSpeed;
  double minHeight;
  double maxHeight;
  PIDController pidController;
};


class ElevatorLift {
 public:
  ElevatorLift(ElevatorConfig *_config);

  void setTarget(double target);
  void onUpdate(double deltaTime, double target);

  void halt();

 private:
  ElevatorConfig *_config;

  double _target;
  double _currentHeight;

  double pulleyRatio = 16 / 42;

};