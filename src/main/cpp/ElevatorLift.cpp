#include "ElevatorLift.h"


ElevatorLift::ElevatorLift(ElevatorConfig *config, frc::Joystick *joystick) : _config(config), _joystick(joystick), _pid("", config->pidConfig) {}

void ElevatorLift::SetSetpoint(units::meter_t setpoint) {
  _setpoint = setpoint;
}


void ElevatorLift::OnUpdate(units::second_t dt) {
  units::volt_t voltage{0};
  // voltage = _pid.Calculate(_currentHeight, dt, 1.2_V);



  // if (voltage > 6_V) {
    // voltage = 6_V;
  // }
}