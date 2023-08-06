#pragma once

#include <thread>
#include <atomic>

// frc libs
// #include <frc/DigitalOutput.h> // old style
#include <frc/Timer.h>
#include <units/time.h>
#include <units/frequency.h>
#include <hal/HAL.h>
#include <frc/SensorUtil.h>
#include <frc/Errors.h>

#include "hal/PPM.h"

/**
 * @brief A class for controlling a PPM signal using DIO pins on the rio
 * 
 */
class PPMController {
 public:

  /**
   * @brief Construct a new Non blocking PPMController object
   * 
   * @param channel 0-9 are on-board PWM
   */
  explicit PPMController(int channel) {
    _channel = channel;
  }

  /**
   * @brief Destroy the PPMController object
   */
  ~PPMController() {
    destroy();
  }

  /**
   * @brief Intialize the PPMController HAL object
   * 
   */
  void init() {
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

  /**
   * @brief Set the Channel/switch the Channel
   * 
   * @param channel 
   */
  void setPPMChannel(int channel) {
    if (frc::SensorUtil::CheckPWMChannel(channel)) {
      destroy();
      _channel = channel;
      init();
    }
  }

  /**
   * @brief Get the Channel object
   * 
   * @return int 
   */
  int getPPMChannel() {
    return _channel;
  }

  /**
   * @brief Set the Config object
   * 
   * @param minPPM 
   * @param deadbandMinPPM 
   * @param centerPPM 
   * @param deadbandMaxPPM 
   * @param maxPPM 
   */
  void setConfig(units::microsecond_t minPPM, units::microsecond_t deadbandMinPPM, units::microsecond_t centerPPM, units::microsecond_t deadbandMaxPPM, units::microsecond_t maxPPM) {
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

  /**
   * @brief Set the Pulse Width object [i.e 1ms to 2ms for standard PPM receivers]
   * 
   * @param pulseWidth 
   * 
   */
  void setPulseWidth(units::microsecond_t pulseWidth) {
    int32_t status = 0;
    HAL_SetPPMPulseTimeMicroseconds(_ppmHandle, pulseWidth.to<int32_t>(), &status);

    if (status != 0) {
      throw FRC_MakeError(status, "PPM Set Pulse Width error Channel {}", _portHandle);
    }
  }

 private:
  void destroy() {
    int32_t status = 0;
    HAL_FreePPMPort(_ppmHandle, &status);
    if (status != 0) {
      throw FRC_MakeError(status, "PPM Destroy error Channel {}", _portHandle);
    }
  }

  enum class State {
    kLow, // 0
    kHigh, // 1
  } _state = State::kLow;

  int _channel;
  HAL_PortHandle _portHandle;
  HAL_DigitalHandle _ppmHandle;
};