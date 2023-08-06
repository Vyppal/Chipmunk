#pragma once

#include "ppm/PPMMotor.h"

/**
 * @brief PPM Flipsky motor controller
 * 
 * The configuration needed for the vesc controller on the mc side is duty cycle.
 * Reconfigure the motors one at a time, set the vesc controllers to duty cycle and let it sit.
 * 
 * 
 */
class PPMFlipsky : public PPMMotor {
 public:
  explicit PPMFlipsky(int channel) : PPMMotor(channel, 0.25_ms, 0.75_ms, 1.25_ms) {}

  PPMFlipsky(PPMFlipsky&&) = default;
  PPMFlipsky& operator=(PPMFlipsky&&) = default;
};