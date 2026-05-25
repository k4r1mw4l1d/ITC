/*
 * ============================================================
 * nRF24L01 + Motor Controller Main Receiver
 * Board: ESP32
 * ============================================================
 */

#include "NRF_Module.h"
#include "Motor_Module.h"

#define NRF_CE_PIN  4
#define NRF_CSN_PIN 5

const uint32_t SIGNAL_TIMEOUT_MS = 500;
uint32_t lastSignalTime = 0;

void setup() {
  Serial.begin(115200); 
  Serial.println("[BOOT] ESP32 Receiver starting...");

  initMotors();
  Serial.println("[MOTORS] Initialized.");

  if (!initRadio(NRF_CE_PIN, NRF_CSN_PIN)) {
    Serial.println("[ERROR] nRF24L01 not found! Check wiring.");
    while (true) delay(1000);
  }
  Serial.println("[NRF] Listening for data...");

  lastSignalTime = millis();
}

void loop() {
  AnalogPayload payload;

  if (checkRadioData(payload)) {
    lastSignalTime = millis();

    Serial.printf("LX=%4d   LY=%4d\n", payload.lx, payload.ly);

    int forwardSpeed = -payload.ly; 
    int turnSpeed = payload.lx;

    drive(forwardSpeed, turnSpeed);
  }

  // Failsafe action
  if (millis() - lastSignalTime > SIGNAL_TIMEOUT_MS) {
    stopAll();
  }
}