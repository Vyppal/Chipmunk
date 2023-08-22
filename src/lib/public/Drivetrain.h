#pragma once

#include "Gearbox.h"

class Drivetrain {
 public:
  Drivetrain(Gearbox &left, Gearbox &right) : _left(left), _right(right) {}

  void set(double leftPower, double rightPower) {
    _left.set(leftPower);
    _right.set(rightPower);
  }

 private:
  Gearbox &_left;
  Gearbox &_right;
};