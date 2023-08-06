/**
 * DON'T TOUCH THIS FILE
 */

/**
 * @brief Based off of the PWM Hal system from wpi https://github.com/wpilibsuite/allwpilib/tree/main/hal
 * Just an editable version to tweak if need be for PPM signals
 */

#ifndef HAL_PPM_H
#define HAL_PPM_H

#include <stdint.h>
#include <hal/HAL.h>
#include <hal/Types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

HAL_DigitalHandle HAL_InitializePPMPort(HAL_PortHandle portHandle, const char *allocationLocation, int32_t *status);

void HAL_FreePPMPort(HAL_DigitalHandle ppmPortHandle, int32_t *status);

HAL_Bool HAL_CheckPPMChannel(int32_t channel);

void HAL_SetPPMConfigMicroseconds(HAL_DigitalHandle ppmPortHandle, int32_t maxPPM, int32_t deadbandMaxPPM, int32_t centerPPM, int32_t deadbandMinPPM, int32_t minPPM, int32_t *status);

void HAL_GetPPMConfigMicroseconds(HAL_DigitalHandle ppmPortHandle, int32_t *maxPPM, int32_t *deadbandMaxPPM, int32_t *centerPPM, int32_t *deadbandMinPPM, int32_t *minPPM, int32_t *status);

void HAL_SetPPMEliminateDeadband(HAL_DigitalHandle ppmPortHandle, HAL_Bool eliminateDeadband, int32_t *status);

HAL_Bool HAL_GetPPMEliminateDeadband(HAL_DigitalHandle ppmPortHandle, int32_t *status);

void HAL_SetPPMPulseTimeMicroseconds(HAL_DigitalHandle ppmPortHandle, int32_t microsecondPulseTime, int32_t *status);

void HAL_SetPPMSpeed(HAL_DigitalHandle ppmPortHandle, double speed, int32_t *status);

void HAL_SetPPMPosition(HAL_DigitalHandle ppmPortHandle, double position, int32_t *status);

void HAL_SetPPMDisabled(HAL_DigitalHandle ppmPortHandle, int32_t *status);

int32_t HAL_GetPPMPulseTimeMicroseconds(HAL_DigitalHandle ppmPortHandle, int32_t *status);

double HAL_GetPPMSpeed(HAL_DigitalHandle ppmPortHandle, int32_t *status);

double HAL_GetPPMPosition(HAL_DigitalHandle ppmPortHandle, int32_t *status);

void HAL_LatchPPMZero(HAL_DigitalHandle ppmPortHandle, int32_t *status);

void HAL_SetPPMPeriodScale(HAL_DigitalHandle ppmPortHandle, int32_t squelchMask, int32_t *status);

void HAL_SetPPMAlwaysHighMode(HAL_DigitalHandle ppmPortHandle, int32_t *status);

int32_t HAL_GetPPMLoopTiming(int32_t *status);

uint64_t HAL_GetPPMCycleStartTime(int32_t *status);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // HAL_PPM_H


