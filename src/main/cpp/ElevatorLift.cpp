// #include "ElevatorLift.h"


// ElevatorLift::ElevatorLift(ElevatorConfig *config, frc::Joystick *joystick) : _config(config), _joystick(joystick), _pid("", config->pidConfig) {}

// void ElevatorLift::SetSetpoint(units::meter_t setpoint) {
//   _setpoint = setpoint;
// }


// void ElevatorLift::OnUpdate(units::second_t dt) {
//   if (_joystick->GetTriggerPressed()) {
//     _setpoint = (_config->maxHeight - _config->minHeight) * ((_joystick->GetZ() + 1) / 2) + _config->minHeight;
    
//     double relativeDifference = (_setpoint - _currentHeight) / (_config->maxHeight - _config->minHeight);

//     relativeDifference = relativeDifference > 1 ? 1 : relativeDifference;
//     relativeDifference = relativeDifference < 0 ? 0 : relativeDifference;

//     double elevatorPower = std::tanh((1.5 * std::pow(relativeDifference, 3) + 0.3 * relativeDifference));
//     _config->motor.set(elevatorPower);
//     _currentHeight += CalculateDisplacement(elevatorPower, dt.value());

//   } else {
//     _config->motor.set(0);
//   }

// }