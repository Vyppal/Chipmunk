#pragma once
// our libs
#include "motorcontrol/MotorController.h"
#include "motorcontrol/PPMFlipsky.h"
#include "ppm/PPMMotor.h"
// std
#include <vector>

class Gearbox {
 public:
  Gearbox(std::string name, std::vector<PPMMotor> motors) : _motors(motors) {
    // int numberOfMotors = motors.size();
    // for (int i = 0; i < numberOfMotors; i++) {
    //   _motors.push_back(motors[i]);
    // }
  }

  void set(double power) {
    int numberOfMotors = _motors.size();
    for (int i = 0; i < numberOfMotors; i++) {
      _motors[i].set(power);
    }
  }

  // collection vector MotorController
 private:
  std::vector<PPMMotor> _motors; 
};