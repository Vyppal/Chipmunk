#include "ppm/PPMController.h"
#include "hal/PPM.h"

// frc libs
#include <frc/Errors.h>
#include <frc/SensorUtil.h>

void PPMController::init() {
  if (!frc::SensorUtil::CheckPWMChannel(_channel)) {
    throw FRC_MakeError(frc::err::ChannelIndexOutOfRange, "PWM Channel {}", _channel);
  }

  _portHandle = HAL_GetPort(_channel);
  std::string name = std::string("PPM: ") + std::to_string(_portHandle);

  int32_t status = 0;
  _ppmHandle = HAL_InitializePPMPort(_portHandle, name.c_str(), &status);

  if (status != 0) {
    throw FRC_MakeError(status, "PPM Creation error Channel {}", _portHandle);
  }

  status = 0;
  HAL_SetPPMDisabled(_ppmHandle, &status);

  if (status != 0) {
    throw FRC_MakeError(status, "PPM Set Disabled error Channel {}", _portHandle);
  }

  status = 0;
  HAL_SetPPMEliminateDeadband(_ppmHandle, false, &status);

  if (status != 0) {
    throw FRC_MakeError(status, "PPM Set Eliminate Deadband error Channel {}", _portHandle);
  }

  if (status != 0) {
    throw FRC_MakeError(status, "PPM Set Period Scale error Channel {}", _portHandle);
  }
}

void PPMController::setPPMChannel(int channel) {
if (frc::SensorUtil::CheckPWMChannel(channel)) {
    destroy();
    _channel = channel;
    init();
  }
}

void PPMController::setConfig(units::microsecond_t minPPM, units::microsecond_t deadbandMinPPM, units::microsecond_t centerPPM, units::microsecond_t deadbandMaxPPM, units::microsecond_t maxPPM) {
  int32_t status = 0;

  HAL_SetPPMConfigMicroseconds(
    _ppmHandle, 
    maxPPM.to<int32_t>(), 
    deadbandMaxPPM.to<int32_t>(), 
    centerPPM.to<int32_t>(), 
    deadbandMinPPM.to<int32_t>(), 
    minPPM.to<int32_t>(), 
    &status
  );

  if (status != 0) {
    throw FRC_MakeError(status, "PPM Set Config error Channel {}", _portHandle);
  }
}

void PPMController::setPulseWidth(units::microsecond_t pulseWidth) {
  int32_t status = 0;
  HAL_SetPPMPulseTimeMicroseconds(_ppmHandle, pulseWidth.to<int32_t>(), &status);

  if (status != 0) {
    throw FRC_MakeError(status, "PPM Set Pulse Width error Channel {}", _portHandle);
  }
}

void PPMController::destroy() {
  int32_t status = 0;
  HAL_FreePPMPort(_ppmHandle, &status);
  if (status != 0) {
    throw FRC_MakeError(status, "PPM Destroy error Channel {}", _portHandle);
  }
}