
struct Motor {
  int controlPin1;
  int controlPin2;
  int enablePin;
  int motorSpeed;
};

void setMotorSpeed(Motor* motor);
void stopMotor(Motor* motor);
void moveForward(Motor* motor);
void moveBackward(Motor* motor);
long measureDistance();

