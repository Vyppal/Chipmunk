#pragma once

#include "motorcontrol/MotorController.h"
#include "ppm/PPMController.h"


/**
 * @brief PPM Motor controller with motor controller base class
 * 
 */
class PPMMotor : public MotorController, private PPMController {
 public:

  /**
   * @brief Construct a new PPM signal Motor
   * 
   * @param channel 
   */
  explicit PPMMotor(int channel);

  /**
   * @brief Construct a new PPMMotor object with custom bounds (default is 1ms, 1.5ms and 2ms) and update rate (default is 100hz)
   * 
   * @param channel 
   * @param min 
   * @param neutral 
   * @param max 
   */
  explicit PPMMotor(int channel, units::microsecond_t min, units::microsecond_t neutral, units::microsecond_t max);
  /**
   * @brief Set the Bounds PPM signal
   * 
   * @param min minimum pulse width in pulse time (-100%)
   * @param neutral neutral pulse width in pulse time (0%)
   * @param max max pulse width in time pulse (+100%)
   */
  virtual void setPPMBounds(units::microsecond_t min, units::microsecond_t neutral, units::microsecond_t max);

  /**
   * @brief Set the Deadband of the PPM signal
   * 
   * @param min 
   * @param max 
   */
  virtual void setPPMDeadband(units::microsecond_t min, units::microsecond_t max);

  /**
   * @brief Set the Channel of the motor controller (on the PWM port)
   * 
   * @param channel 
   */
  virtual void setChannel(int channel);

  /**
   * @brief Get the PWM Channel that the motor is on
   * 
   * @return int 
   */
  virtual int getChannel();

  /**
   * @brief Set the power of the motor, -1 to 1
   * 
   * @param power 
   */
  virtual void set(double power) override;

  /**
   * @brief Disable the motor
   * 
   */
  virtual void disable() override;

 private:
  struct Bounds {
    units::microsecond_t min = 1_ms;
    units::microsecond_t deadbandMin = 1.5_ms;
    units::microsecond_t neutral = 1.5_ms;
    units::microsecond_t deadbandMax = 1.5_ms;
    units::microsecond_t max = 2_ms;
  } _bounds;
};