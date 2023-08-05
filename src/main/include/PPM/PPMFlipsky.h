#pragma once

#include "PPMMotor.h"

/**
 * @brief PPM Flipsky motor controller
 * 
 */
class PPMFlipsky : public PPMMotor {
 public:
  explicit PPMFlipsky(int channel) : PPMMotor(channel, 1_ms, 1.5_ms, 2_ms) {}

  PPMFlipsky(PPMFlipsky&&) = default;
  PPMFlipsky& operator=(PPMFlipsky&&) = default;
};