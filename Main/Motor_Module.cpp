#include "Motor_Module.h"x`

void setMotor(uint8_t dirPin, uint8_t pwmCh, int speed) {
  speed = constrain(speed, -MAX_SPEED, MAX_SPEED);

  if (speed > 0) {
    digitalWrite(dirPin, HIGH);
    ledcWrite(pwmCh, speed);
  } 
  else if (speed < 0) {
    digitalWrite(dirPin, LOW);
    ledcWrite(pwmCh, -speed);
  } 
  else {
    ledcWrite(pwmCh, 0);
  }
}

int applyDeadzone(int val) {
  if (val > -DEADZONE && val < DEADZONE) return 0;
  return val;
}

void initMotors() {
  pinMode(PIN_DIR_RIGHT, OUTPUT);
  pinMode(PIN_DIR_LEFT, OUTPUT);

  ledcSetup(CH_RIGHT, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_PWM_RIGHT, CH_RIGHT);

  ledcSetup(CH_LEFT, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_PWM_LEFT, CH_LEFT);

  stopAll();
}

void drive(int forward, int turn) {
  forward = applyDeadzone(forward);
  turn = applyDeadzone(turn);

  int right = forward - turn;
  int left  = forward + turn;

  int maxVal = max(abs(right), abs(left));
  if (maxVal > MAX_SPEED) {
    right = (right * MAX_SPEED) / maxVal;
    left  = (left  * MAX_SPEED) / maxVal;
  }

  setMotor(PIN_DIR_RIGHT, CH_RIGHT, right);
  setMotor(PIN_DIR_LEFT, CH_LEFT, left);
}

void stopAll() {
  setMotor(PIN_DIR_RIGHT, CH_RIGHT, 0);
  setMotor(PIN_DIR_LEFT, CH_LEFT, 0);
}