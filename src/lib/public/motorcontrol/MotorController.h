#pragma once

#include <units/voltage.h>

/**
 * @brief Abstract concept for motor controller which can be used as a base for other controllers
 * 
 */
class MotorController {
 public:
  /**
   * @brief Construct a new Motor Controller object
   * 
   */
  MotorController() = default;

  /**
   * @brief Set the Deadband of the motor, default is 0.0, 0.0 (minimum must be negative, maximum must be positive)
   * If the power supplied is not 0 but is between the deadband, the power will scale in the deadband direction.
   * I.e, if the  min deadband is -0.1, and the power supplied is -0.05, the motor will be provided with -0.1 regardless.
   * This can solve a few problems when a small voltage or power is supplied to the motor and it does not move. (friction or under load etc..)
   * 
   * @param min 
   * @param max 
   */
  virtual void setDeadband(double min, double max) {
    _deadbandMin = min > 0 ? 0 : min;
    _deadbandMax = max < 0 ? 0 : max;
  }

  /**
   * @brief Set the Deadband of the motor in voltage, default is 0.0, 0.0 (minimum must be negative, maximum must be positive)
   * If the power supplied is not 0 but is between the deadband, the power will scale in the deadband direction.
   * I.e, if the  min deadband is -0.1, and the power supplied is -0.05, the motor will be provided with -0.1 regardless.
   * This can solve a few problems when a small voltage or power is supplied to the motor and it does not move. (friction or under load etc..)
   * 
   * @param min 
   * @param max 
   */
  void setDeadbandVoltage(units::volt_t min, units::volt_t max) {
    units::dimensionless::scalar_t minScalar = min / 12_V;
    units::dimensionless::scalar_t maxScalar = max / 12_V;
    setDeadband(minScalar.to<double>(), maxScalar.to<double>());
  }

  /**
   * @brief Set the power of the motor, -1 to 1
   * 
   * @param power 
   */
  virtual void set(double power) = 0;

  /**
   * @brief Set the Voltage of the motor, -12 to 12
   * 
   * @param power 
   */
  void setVoltage(units::volt_t power) {
    units::dimensionless::scalar_t powerScalar = power / 12_V;
    set(powerScalar.to<double>());
  }

  /**
   * @brief Get the power of the motor, -1 to 1
   * 
   * @return double 
   */
  virtual double get() {
    return _power;
  }

  /**
   * @brief Get the Voltage the motor is running at, -12 to 12
   * 
   * @return units::volt_t 
   */
  virtual units::volt_t getVoltage() {
    return get() * 12_V;
  }

  /**
   * @brief Set the motor inverted (reverses direction)
   * 
   * @param invert 
   */
  virtual void setInvert(bool invert) {
    _inverted = invert;
  };

  /**
   * @brief Get if the motor is inverted
   * 
   * @return true 
   * @return false 
   */
  virtual bool getInvert() {
    return _inverted;
  }

  /**
   * @brief enable the motor if it was disabled
   * 
   */
  virtual void enable() {
    _disabled = false;
  }

  /**
   * @brief disable the motor
   * 
   */
  virtual void disable() {
    set(0);
    _disabled = true;
  }

  /**
   * @brief Get if the motor is currently disabled
   * 
   * @return true 
   * @return false 
   */
  virtual bool getDisabled() {
    return _disabled;
  }

 protected:
  double removeDeadband(double power) {
    if (power > 0 && power < _deadbandMax) { // if in range of max deadband
      power = _deadbandMax;
    } else if (power < 0 && power > _deadbandMin) { // if in range of min deadband
      power = _deadbandMin;
    }
    return power;
  }

  double _deadbandMin = 0.0;
  double _deadbandMax = 0.0;

  double _power = 0.0;
  bool _inverted = false;
  bool _disabled = false;
};