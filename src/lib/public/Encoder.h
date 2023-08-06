#pragma once

class Encoder {
 public:
  Encoder(int tickPerRotation);

  virtual int getEncoderRawTicks() = 0;

  virtual int getEncoderRawTicksVelocity() = 0;

  
};