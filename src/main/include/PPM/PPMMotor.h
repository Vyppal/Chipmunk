#pragma once

#include "PPMController.h"
#include <units/voltage.h>
#include <frc/motorcontrol/PWMTalonFX.h>

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
  explicit PPMMotor(int channel) : PPMController(channel) {
    init();
  }

  /**
   * @brief Construct a new PPMMotor object with custom bounds (default is 1ms, 1.5ms and 2ms) and update rate (default is 100hz)
   * 
   * @param channel 
   * @param loopRate_hz 
   * @param min 
   * @param neutral 
   * @param max 
   */
  explicit PPMMotor(int channel, units::microsecond_t min, units::microsecond_t neutral, units::microsecond_t max) : PPMController(channel) {
    init();
    setDeadband(neutral, neutral); // no deadband by default
    setBounds(min, neutral, max);
  }

  /**
   * @brief Set the Bounds of the motor
   * 
   * @param min minimum pulse width in pulse time (-100%)
   * @param neutral neutral pulse width in pulse time (0%)
   * @param max max pulse width in time pulse (+100%)
   */
  virtual void setBounds(units::microsecond_t min, units::microsecond_t neutral, units::microsecond_t max) {
    _bounds.min = min;
    _bounds.neutral = neutral;
    _bounds.max = max;


    setConfig(_bounds.min, _bounds.deadbandMin, _bounds.neutral, _bounds.deadbandMax, _bounds.max);
  }

  /**
   * @brief Set the Deadband of the motor
   * 
   * @param min minimum in pulse time (-deadband) i.e 1.5ms - 0.1ms = 1.4ms
   * @param max maximum in pulse time (+deadband) i.e 1.5ms + 0.1ms = 1.6ms
   */
  virtual void setDeadband(units::microsecond_t min, units::microsecond_t max) {
    _bounds.deadbandMin = min;
    _bounds.deadbandMax = max;

    setConfig(_bounds.min, _bounds.deadbandMin, _bounds.neutral, _bounds.deadbandMax, _bounds.max);
  }
  
  /**
   * @brief Set the Channel of the motor/switch the Channel
   * 
   * @param channel 
   */
  virtual void setChannel(int channel) {
    setPPMChannel(channel);
  }

  /**
   * @brief Get the Channel the motor is running on
   * 
   * @return int 
   */
  virtual int getChannel() {
    return getPPMChannel();
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
   * @brief Enable the motor if it was disabled
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
    units::microsecond_t deadbandMin = 1.5_ms;
    units::microsecond_t neutral = 1.5_ms;
    units::microsecond_t deadbandMax = 1.5_ms;
    units::microsecond_t max = 2_ms;
  } _bounds;

  bool _inverted = false;
  bool _disabled = false;
};