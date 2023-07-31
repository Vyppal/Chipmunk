#pragma once

#include "PPMMotor.h"

class PPMFlipsky : public PPMMotor {
 public:
  explicit PPMFlipsky(int channel) : PPMMotor(channel, 100_Hz, 1_ms, 1.5_ms, 2_ms) {}
  explicit PPMFlipsky(int channel, units::hertz_t loopRate_hz) : PPMMotor(channel, loopRate_hz) {}

  PPMFlipsky(PPMFlipsky&&) = default;
  PPMFlipsky& operator=(PPMFlipsky&&) = default;
};