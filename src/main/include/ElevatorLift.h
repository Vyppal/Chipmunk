#pragma once

#include "PID.h"


#include <units/length.h>
#include <units/time.h>
#include <units/voltage.h>

#include <frc/Joystick.h>

#include "PPM/PPMFlipsky.h"


struct ElevatorConfig {
  PPMFlipsky motor;
  units::meter_t minHeight;
  units::meter_t maxHeight;
  wom::PIDConfig<units::meter, units::volts> pidConfig;
};


class ElevatorLift {
 public:
  ElevatorLift(ElevatorConfig *config, frc::Joystick *joystick);

  void SetSetpoint(units::meter_t setpoint);
  void OnUpdate(units::second_t dt);

 private:
  ElevatorConfig *_config;
  frc::Joystick *_joystick;

  units::meter_t _setpoint;
  
  units::meter_t _currentHeight;

  wom::PIDController<units::meter, units::volts> _pid;

};