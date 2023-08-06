
#include "ppm/PPMMotor.h"

#include <algorithm>

PPMMotor::PPMMotor(int channel) : PPMController(channel) {
  init();
}

PPMMotor::PPMMotor(int channel, units::microsecond_t min, units::microsecond_t neutral, units::microsecond_t max) : PPMController(channel) {
  init();
  setPPMDeadband(neutral, neutral); // no deadband by default
  setPPMBounds(min, neutral, max);
}

void PPMMotor::setPPMBounds(units::microsecond_t min, units::microsecond_t neutral, units::microsecond_t max) {
  _bounds.min = min;
  _bounds.neutral = neutral;
  _bounds.max = max;
  setConfig(_bounds.min, _bounds.deadbandMin, _bounds.neutral, _bounds.deadbandMax, _bounds.max);
}

void PPMMotor::setPPMDeadband(units::microsecond_t min, units::microsecond_t max) {
  _bounds.deadbandMin = min;
  _bounds.deadbandMax = max;
  setConfig(_bounds.min, _bounds.deadbandMin, _bounds.neutral, _bounds.deadbandMax, _bounds.max);
}

void PPMMotor::setChannel(int channel) {
  setPPMChannel(channel);
}

int PPMMotor::getChannel() {
  return getPPMChannel();
}

void PPMMotor::set(double power) {
  // return if disabled
  if (_disabled) {
    return;
  }

  // clamp the power between -1 and 1
  power = std::clamp(power, -1.0, 1.0);
  // invert the power if needed
  power = _inverted ? -power : power;
  // remove the deadband of the motor
  power = removeDeadband(power);
  // range of pulse
  units::microsecond_t range = power < 0 ? (_bounds.neutral - _bounds.min) : (_bounds.max - _bounds.neutral);
  // calculate the pulse width
  units::microsecond_t pulse = _bounds.neutral + (range * power);
  // set the pulse width
  setPulseWidth(pulse);
}

void PPMMotor::disable() {
  set(0);
  _disabled = true;
  setPulseWidth(0_ms);
}