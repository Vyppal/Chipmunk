#pragma once

#include <hal/Types.h>
#include <units/time.h>

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
  void init();

  /**
   * @brief Set the Channel/switch the Channel
   * 
   * @param channel 
   */
  void setPPMChannel(int channel);

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
  void setConfig(units::microsecond_t minPPM, units::microsecond_t deadbandMinPPM, units::microsecond_t centerPPM, units::microsecond_t deadbandMaxPPM, units::microsecond_t maxPPM);

  /**
   * @brief Set the Pulse Width object [i.e 1ms to 2ms for standard PPM receivers]
   * 
   * @param pulseWidth 
   * 
   */
  void setPulseWidth(units::microsecond_t pulseWidth);

 private:
  void destroy();

  enum class State {
    kLow, // 0
    kHigh, // 1
  } _state = State::kLow;

  int _channel;
  HAL_PortHandle _portHandle;
  HAL_DigitalHandle _ppmHandle;
};