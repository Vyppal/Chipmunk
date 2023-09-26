#pragma once

#include <frc/Joystick.h>

class TankDrivebase {
 public:
  TankDrivebase(frc::Joystick *joystick);
  
  void UpdateHeight();


 private:
  TankConfig *_config;
  frc::Joystick *_joystick;
  
};