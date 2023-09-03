#include "ElevatorLift.h"


ElevatorLift::ElevatorLift(ElevatorConfig *config) : _config(config) {}

void ElevatorLift::setTarget(double target) {
  _target = target;
}

void ElevatorLift::onUpdate(double deltaTime, double target) {
  //             = (2 * pi * r) * pulleyRatio * motorPosition
  // _currentHeight = (2 * 3.14159265359 * 0.037) * pulleyRatio * (motor.getTicks() / 42);
  double trueTarget = (target + 1) / 2;
  _target = (_config->maxHeight - _config->minHeight) * trueTarget + _config->minHeight;
  _config->motor.set(_config->pidController.compute(_target, _currentHeight, deltaTime));
}
void ElevatorLift::halt() { _config->motor.set(0); }