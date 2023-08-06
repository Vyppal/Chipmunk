/**
 * DON'T TOUCH THIS FILE
 */

/**
 * @brief Based off of the PWM Hal system from wpi https://github.com/wpilibsuite/allwpilib/tree/main/hal
 * Just an editable version to tweak if need be for PPM signals
 */

#include "hal/PPM.h"

// cpp files
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <thread>

#include <fmt/format.h>

#include <iostream>

#include "hal/PWM.h"

using namespace hal;

// define functions (most of PPM is the same of PWM so I'm just reusing the same functions unless something specific is needed)

/**
 * @brief @TODO
 * 
 * setup the disable limits. I can see the PWM signals still being set to the mc's even after the robot is disabled.
 * Need to setup a proper disable procedure
 * 
 */
extern "C" {

HAL_DigitalHandle HAL_InitializePPMPort(HAL_PortHandle portHandle, const char *allocationLocation, int32_t *status) {
  HAL_DigitalHandle handle = HAL_InitializePWMPort(portHandle, allocationLocation, status);

  // @TODO increase frequency
  if (*status != 0) {
    std::cout << "Port handle no go" << std::endl;
  }

  *status = 0;
  HAL_SetPPMPeriodScale(handle, 3, status); // should equate to 200hz (can use 3 (50hz) if need be. Check when next available)

  if (*status != 0) {
    std::cout << "Period scale set error" << std::endl;
  }
  return handle;
}

void HAL_FreePPMPort(HAL_DigitalHandle ppmPortHandle, int32_t *status) {
  HAL_FreePWMPort(ppmPortHandle, status);
}

HAL_Bool HAL_CheckPPMChannel(int32_t channel) {
  return HAL_CheckPWMChannel(channel);
}

void HAL_SetPPMConfigMicroseconds(HAL_DigitalHandle ppmPortHandle, int32_t maxPPM, int32_t deadbandMaxPPM, int32_t centerPPM, int32_t deadbandMinPPM, int32_t minPPM, int32_t *status) {
  HAL_SetPWMConfigRaw(ppmPortHandle, maxPPM, deadbandMaxPPM, centerPPM, deadbandMinPPM, minPPM, status);
}

void HAL_GetPPMConfigMicroseconds(HAL_DigitalHandle ppmPortHandle, int32_t *maxPPM, int32_t *deadbandMaxPPM, int32_t *centerPPM, int32_t *deadbandMinPPM, int32_t *minPPM, int32_t *status) {
  HAL_GetPWMConfigRaw(ppmPortHandle, maxPPM, deadbandMaxPPM, centerPPM, deadbandMinPPM, minPPM, status);
}

void HAL_SetPPMEliminateDeadband(HAL_DigitalHandle ppmPortHandle, HAL_Bool eliminateDeadband, int32_t *status) {
  HAL_SetPWMEliminateDeadband(ppmPortHandle, eliminateDeadband, status);
}

HAL_Bool HAL_GetPPMEliminateDeadband(HAL_DigitalHandle ppmPortHandle, int32_t *status) {
  return HAL_GetPWMEliminateDeadband(ppmPortHandle, status);
}

void HAL_SetPPMPulseTimeMicroseconds(HAL_DigitalHandle ppmPortHandle, int32_t microsecondPulseTime, int32_t *status) {
  HAL_SetPWMRaw(ppmPortHandle, microsecondPulseTime, status); // the new version uses HAL_SetPWMPulseTimeMicroseconds for some reason. Hasn't been updated through the chain yet
}

void HAL_SetPPMSpeed(HAL_DigitalHandle ppmPortHandle, double speed, int32_t *status) {
  HAL_SetPWMSpeed(ppmPortHandle, speed, status);
}

void HAL_SetPPMPosition(HAL_DigitalHandle ppmPortHandle, double position, int32_t *status) {
  HAL_SetPWMPosition(ppmPortHandle, position, status);
}

void HAL_SetPPMDisabled(HAL_DigitalHandle ppmPortHandle, int32_t *status) {
  HAL_SetPWMDisabled(ppmPortHandle, status);
}

int32_t HAL_GetPPMPulseTimeMicroseconds(HAL_DigitalHandle ppmPortHandle, int32_t *status) {
  return HAL_GetPWMRaw(ppmPortHandle, status);
}

double HAL_GetPPMSpeed(HAL_DigitalHandle ppmPortHandle, int32_t *status) {
  return HAL_GetPWMSpeed(ppmPortHandle, status);
}

double HAL_GetPPMPosition(HAL_DigitalHandle ppmPortHandle, int32_t *status) {
  return HAL_GetPWMPosition(ppmPortHandle, status);
}

void HAL_LatchPPMZero(HAL_DigitalHandle ppmPortHandle, int32_t *status) {
  HAL_LatchPWMZero(ppmPortHandle, status);
}

void HAL_SetPPMPeriodScale(HAL_DigitalHandle ppmPortHandle, int32_t squelchMask, int32_t *status) {
  HAL_SetPWMPeriodScale(ppmPortHandle, squelchMask, status);
}

void HAL_SetPPMAlwaysHighMode(HAL_DigitalHandle ppmPortHandle, int32_t *status) {
  *status = 0;
  // HAL_SetPWMAlwaysHighMode(ppmPortHandle, status); // doesn't exist at all yet
}

int32_t HAL_GetPPMLoopTiming(int32_t *status) {
  return HAL_GetPWMLoopTiming(status);
}

uint64_t HAL_GetPPMCycleStartTime(int32_t *status) {
  return HAL_GetPWMCycleStartTime(status);
}

} // extern "C"