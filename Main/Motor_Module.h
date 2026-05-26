#pragma once

// Changed to safe pins that don't conflict with ESP32 SPI (18, 19, 23)
#define PIN_DIR_RIGHT  14
#define PIN_PWM_RIGHT  27

#define PIN_DIR_LEFT   12
#define PIN_PWM_LEFT   13

#define PWM_FREQ 1000
#define PWM_RES 8

#define CH_RIGHT 0
#define CH_LEFT 1

#define DEADZONE 7
#define MAX_SPEED 220

void initMotors();
void drive(int forward, int turn);
void stopAll();