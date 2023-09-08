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

  void onUpdate(double deltaTime, double target);
  void unnamedFunction1();

  void halt();

 private:
  ElevatorConfig *_config;

  double _requestedSpeed;
  // double _currentHeight;

  double _currentSpeed;

  double maxElevatorSpeed = 3; // m/s

  double pulleyRatio = 16 / 42;

  int _prevTick = 0;
  int _currentTick = 0;


  double currentWarningThreshold = 1500; // needs testing
  int warningCounter = 0;
  int warningCounterThreshold = 25; // around 0.5 seconds (10 at 50Hz)

  int limitedDirection = 0; // -1 if limit down, 1 if limit up, 0 if no limit

};