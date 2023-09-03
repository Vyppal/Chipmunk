// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>



#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Joystick.h>
// #include <frc/Timer.h>

// our libs
#include "RobotMap.h"
#include "TankDrivebase.h"
#include "ElevatorLift.h"
#include "Time.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

 private:
  RobotMap *_robotMap;
  TankDrivebase *_tankDrivebase;
  ElevatorLift *_elevator;
  int startTime = std::time(nullptr);
  int currentTime =std::time(nullptr);
  int prevTime = std::time(nullptr);
  
};
