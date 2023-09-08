#include "ElevatorLift.h"


ElevatorLift::ElevatorLift(ElevatorConfig *config) : _config(config) {}

// current
// voltage
// encoder value (rotational velocity)


void ElevatorLift::onUpdate(double deltaTime, double speedTarget, int directionRequest) {
  _currentTick = _config->motor.getEncoderValue();
  if (directionRequest == 0) {
    _prevTick = _currentTick;
    _requestedSpeed = 0;
    halt();
    return;
  }
  _requestedSpeed = (speedTarget + 1) / 2 * maxElevatorSpeed * directionRequest; // snapping range of -1->1 to 0->1 then multiplying by max elevator speed then by direction
  _currentSpeed = (2 * 3.14159265359 * 0.037) * pulleyRatio * ((_currentTick - _prevTick) * deltaTime / 42);
  
  unnamedFunction(directionRequest);
  
  _config->motor.set(_config->pidController.compute(_requestedSpeed, _currentSpeed, deltaTime));
  _prevTick = _currentTick;
}
void ElevatorLift::halt() { _config->motor.set(0); }

void ElevatorLift::unnamedFunction1(int directionRequest) {
  // ensures that elevator doesn't want to keep going up or down if too high or low (it checks its height based on abnormally high current values that last a duration of time)
  if (directionRequest == 0) {  return;  }
  if (_config->motor.getCurrent() < currentWarningThreshold) {  limitedDirection = 0; return;  }
  warningCounter++;
  if (warningCounter < warningCounterThreshold) {  limitedDirection = 0; return;  }
  warningCounter = 0;
  limitedDirection = directionRequest;
}