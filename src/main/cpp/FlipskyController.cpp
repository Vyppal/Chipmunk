#include "FlipskyController.h"

Flipsky::Flipsky(FlipskyConfig config, int portNum, bool registableSender) : _config(config), _portNum(portNum), _registableSender(registableSender), _pid(config.path + "/pid", config.pidConfig) {
  motor = new frc::PWM{portNum, registableSender};
  
}

void Flipsky::SetSpeed() {
  // make changes to work with max speed
  // motor.SetSpeed();
}

units::volt_t Flipsky::GetSpeed() {
  return motor->GetSpeed() * 1_V;
}

void Flipsky::SetPosition(double pos) {
  motor->SetPosition(pos);
}

units::radian_t Flipsky::GetPosition() {
  return 1_rad;
}

void Flipsky::OnUpdate() {

}