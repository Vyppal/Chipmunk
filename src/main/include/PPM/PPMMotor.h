#pragma once

#include "PPMController.h"
#include <units/voltage.h>

/**
 * @brief Create a PPM DIO Motor object
 * 
 */
class PPMMotor : private PPMController {
 public:

  /**
   * @brief Construct a new PPMMotor object with default bounds
   * 
   * @param channel 
   */
  explicit PPMMotor(int channel) : PPMController(channel) {}

  /**
   * @brief Construct a new PPMMotor object with custom bounds (default is 1ms, 1.5ms and 2ms) and update rate (default is 100hz)
   * 
   * @param channel 
   * @param loopRate_hz 
   * @param min 
   * @param neutral 
   * @param max 
   */
  explicit PPMMotor(int channel, units::microsecond_t min, units::microsecond_t neutral, units::microsecond_t max) : PPMController(channel, 100_Hz) {
    _bounds.min = min;
    _bounds.neutral = neutral;
    _bounds.max = max;
  }
  
  /**
   * @brief Set the Channel of the motor/switch the Channel
   * 
   * @param channel 
   */
  virtual void setChannel(int channel) {
    setDIOChannel(channel);
  }

  /**
   * @brief Get the Channel the motor is running on
   * 
   * @return int 
   */
  virtual int getChannel() {
    return getDIOChannel();
  }

  /**
   * @brief Set the power of the motor, -1 to 1
   * 
   * @param power 
   */
  virtual void set(double power) {
    if (_disabled) {
      return;
    }

    power = std::clamp(power, -1.0, 1.0);
    power = _inverted ? -power : power;
    units::microsecond_t range = power < 0 ? (_bounds.neutral - _bounds.min) : (_bounds.max - _bounds.neutral);
    units::microsecond_t pulse = _bounds.neutral + (range * power);
    setPulseWidth(pulse);
  }

  /**
   * @brief Set the Voltage object, -12 to 12
   * 
   * @param voltage 
   */
  virtual void setVoltage(units::volt_t voltage) {
    units::dimensionless::scalar_t power = voltage / 12_V;
    set(power);
  }

  /**
   * @brief Invert the motor
   * 
   * @param invert 
   */
  virtual void setInvert(bool invert) {
    _inverted = invert;
  }

  /**
   * @brief Check if the motor is inverted
   * 
   * @return true 
   * @return false 
   */
  virtual bool getInvert() {
    return _inverted;
  }

  /**
   * @brief enable the motor, best during teleop init
   * 
   */
  virtual void enable() {
    _disabled = false;
  }

  /**
   * @brief Disable the motor
   * 
   */
  virtual void disable() {
    set(0);
    _disabled = true;
  }

  /**
   * @brief Stop the motor completely, disable and set pulse width to 0 (NOT NEUTRAL)
   * 
   */
  virtual void stopMotor() {
    disable();
    setPulseWidth(0_ms);
  }

 private:
  struct Bounds {
    units::microsecond_t min = 1_ms;
    units::microsecond_t neutral = 1.5_ms;
    units::microsecond_t max = 2_ms;
  } _bounds;

  bool _inverted = false;
  bool _disabled = true;
};