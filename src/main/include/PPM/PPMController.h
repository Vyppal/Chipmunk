#pragma once

#include <frc/DigitalOutput.h>
#include <frc/Timer.h>
#include <units/time.h>
#include <units/frequency.h>
#include <thread>
#include <atomic>

/**
 * @brief A class for controlling a PPM signal using DIO pins on the rio
 * 
 */
class PPMController {
 public:

  /**
   * @brief Construct a new Non blocking PPMController object, this will need to be updated every loop cycle using `update()`
   * 
   * @param channel 0-9 are on-board DIO, 10-19 are on the MXP port
   */
  explicit PPMController(int channel) : _output(channel) {
    _lastPulse = frc::Timer::GetFPGATimestamp();
  }

  /**
   * @brief Construct a new Asynchronous PPMController object, this will update automatically when constructed with the desired update rate `loopRate_hz`
   * No need to call update() when using this constructor
   * 
   * @param channel 
   * @param loopRate_hz 
   */
  explicit PPMController(int channel, units::hertz_t loopRate_hz) : _output(channel) {
    _lastPulse = frc::Timer::GetFPGATimestamp();
    _running = true;

    // Lambda thread for async loop
    _loop_t = std::thread([this, loopRate_hz] {
      while (_running) {
        update();
        frc::Wait(1_s / (loopRate_hz.to<int>())); // not even sure why I bothered with the units here, I have to convert it anyway...
      }
    });
  }

  /**
   * @brief Destroy the PPMController object
   * This is rather important because if a thread was created it needs to be stopped and joined with the main thread
   */
  ~PPMController() {
    _running = false;
    if (_loop_t.joinable()) {
      _loop_t.join();
    }
  }

  /**
   * @brief Set the Channel/switch the Channel
   * 
   * @param channel 
   */
  void setDIOChannel(int channel) {
    _output = frc::DigitalOutput(channel);
  }

  /**
   * @brief Get the Channel object
   * 
   * @return int 
   */
  int getDIOChannel() {
    return _output.GetChannel();
  }

  /**
   * @brief Set the Pulse Width object [i.e 1ms to 2ms for standard PPM receivers]
   * 
   * @param pulseWidth 
   */
  void setPulseWidth(units::microsecond_t pulseWidth) {
    _pulseWidth = pulseWidth;
  }

  /**
   * @brief Set the Update Rate object [i.e 20ms for standard PPM signal (can't be lower than the pulse width)]
   * 
   * @param updateRate 
   */
  void setUpdateRate(units::microsecond_t updateRate) {
    _updateRate = updateRate;
  }

  /**
   * @brief Update the PPM signal and state. This should be called every loop cycle if using the non-blocking constructor
   * 
   */
  void update() {
    std::cout << "Test" << std::endl;
    units::microsecond_t now = frc::Timer::GetFPGATimestamp(); // get the current time
    units::microsecond_t difference = now - _lastPulse; // get the difference between the current time and the last pulse
    switch (_state) {
      case State::kLow:
        if (difference >= _updateRate) {
          // Start Pulse
          _output.Set(true);
          _lastPulse = now;
          _state = State::kHigh;
        }
        break;
      case State::kHigh:
        if (difference >= _pulseWidth) {
          // End Pulse
          _output.Set(false);
          _lastPulse = now;
          _state = State::kLow;
        }
        break;
    }
  }

 private:
  enum class State {
    kLow, // 0
    kHigh, // 1
  } _state = State::kLow;

  frc::DigitalOutput _output; // 0-9 are on-board, 10-19 are on the MXP port
  units::microsecond_t _pulseWidth; // pulse width in the update range [i.e 1ms to 2ms]
  units::microsecond_t _updateRate; // update rate that the pulse resides in [20ms default]
  units::microsecond_t _lastPulse = 0_ms;

  std::thread _loop_t; // thread for if this runs async
  std::atomic<bool> _running = std::atomic<bool>(false); // atomic bool for if the loop is running
};