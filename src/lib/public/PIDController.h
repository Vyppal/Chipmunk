#pragma once 

class PIDController {
 public:
  PIDController(double kp, double ki, double kd) : _kp(kp), _ki(ki), _kd(kd) {}
  double compute(double goal, double input, double deltaTime) {
    double currentError = goal - input;
    double derivative = (currentError - _previousError) / deltaTime;
    _integralSum += currentError * deltaTime;
    _previousError = currentError;

    // Auto-tuning logic
    if (_tuningStep < TUNING_STEPS) {
      _oscillationAmplitude += fabs(currentError);
      _tuningStep++;

      if (_tuningStep == TUNING_STEPS) {
        // Auto-tuning is complete, calculate gains
        double averageAmplitude = _oscillationAmplitude / TUNING_STEPS;
        _kp = 0.6 / averageAmplitude;
        _ki = 1.2 / (averageAmplitude * deltaTime);
        _kd = 0.075 / (averageAmplitude / deltaTime);
      }
    }

    return (_kp * currentError) + (_ki * _integralSum) + (_kd * derivative); // output
  }

 private:
  double _kp;  // Proportional gain
  double _ki;  // Integral gain
  double _kd;  // Derivative gain
  double _integralSum = 0;  // Integral accumulator
  double _previousError = 0;  // Previous error

  // Auto-tuning variables
  int _tuningStep = 0;  // Step in the auto-tuning process
  double _oscillationAmplitude = 0;  // Amplitude of oscillation during tuning

  static const int TUNING_STEPS = 50;  // Number of steps for auto-tuning
};