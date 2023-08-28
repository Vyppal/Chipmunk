#pragma once
// our libs
#include "motorcontrol/MotorController.h"

// std
#include <vector>

class Gearbox {
 public:
  Gearbox(std::string name, std::vector<MotorController> motors) {
    _motors = motors;
  }

  void set(double power) {
    for (auto motor : _motors) {
      motor.set(power);
    }
  }

  // collection vector MotorController
 private:
  std::vector<MotorController> _motors; 
};