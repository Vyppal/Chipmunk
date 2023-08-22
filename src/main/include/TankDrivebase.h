#include "Drivetrain.h"

class TankDrivebase {
  public:
    TankDrivebase(Drivetrain &drivetrain) : _drivetrain(drivetrain) {}
  
    // void onAttach() override {
    //   // nothing to do
    // }

    // void onUpdate() override {
      
    // }
  private:
    Drivetrain &_drivetrain;
};