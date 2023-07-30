#pragma once

#include <frc/PWM.h>
#include "PID.h"

#include <units/voltage.h>
#include <units/angle.h>


// INCOMPLETE

struct FlipskyConfig {
  std::string path;
  wom::PIDConfig<units::radian, units::volt> pidConfig;
};

enum class MotorState {
  kPositionControl,
  kSpeedControl
};

class Flipsky {
 public:
  Flipsky(FlipskyConfig config, int portNum, bool registableSender);

  void SetSpeed();
  units::volt_t GetSpeed();

  void SetPosition(double pos);
  units::radian_t GetPosition();

  void OnUpdate();


 private:
  frc::PWM *motor;
  wom::PIDController<units::radian, units::volt> _pid;

  int _portNum;
  bool _registableSender;

  FlipskyConfig _config;

};