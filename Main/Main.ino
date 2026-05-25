/*
 * ============================================================
 * nRF24L01 Receiver – Arduino Uno
 * Lib : RF24 by TMRh20
 * ============================================================
 *
 * nRF24L01 wiring for Arduino Uno:
 * ┌─────────────┬────────────┐
 * │ nRF24 pin   │ Uno pin    │
 * ├─────────────┼────────────┤
 * │ VCC         │ 3.3 V      │
 * │ GND         │ GND        │
 * │ CE          │ Pin 7      │
 * │ CSN         │ Pin 8      │
 * │ SCK         │ Pin 13     │
 * │ MOSI        │ Pin 11     │
 * │ MISO        │ Pin 12     │
 * └─────────────┴────────────┘
 */

#include "NRF_Module.h"

#define NRF_CE_PIN  7
#define NRF_CSN_PIN 8

void setup() {
  Serial.begin(9600);   // Uno works best at 9600
  Serial.println("nRF24 Receiver starting...");

  // Initialize the radio using our procedural function
  if (!initRadio(NRF_CE_PIN, NRF_CSN_PIN)) {
    Serial.println("ERROR: nRF24L01 not found! Check wiring.");
    while (true) delay(1000);
  }

  Serial.println("Listening for data...");
  Serial.println("   LX      LY");
  Serial.println("-------  -------");
}

void loop() {
  AnalogPayload payload;

  // Pass the payload struct instance by reference to be updated
  if (checkRadioData(payload)) {
    Serial.print("LX=");
    Serial.print(payload.lx);
    Serial.print("   LY=");
    Serial.println(payload.ly);
  }
}