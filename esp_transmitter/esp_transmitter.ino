#include <Arduino.h>
#include <ps5Controller.h>
#include <SPI.h>
#include <RF24.h>

#define NRF_CE_PIN   4
#define NRF_CSN_PIN  5

RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);

const byte ADDRESS[6] = "PS5TX";

struct AnalogPayload {
  int8_t lx;
  int8_t ly;
};

const uint16_t SEND_INTERVAL_MS = 20;
uint32_t lastSend = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\n[BOOT] PS5 → nRF24 Transmitter starting…");

  if (!radio.begin()) {
    Serial.println("[ERROR] nRF24L01 not found! Check wiring.");
    while (true) delay(1000);
  }

  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(108);
  radio.openWritingPipe(ADDRESS);
  radio.stopListening();
  radio.setAutoAck(true);
  radio.setRetries(5, 15);

  Serial.println("[NRF] Radio initialised.");

  ps5.begin("1a:2b:3c:01:01:01");   // <-- replace with your controller's MAC
  Serial.println("[PS5] Waiting for controller…");
}

void loop() {
  if (!ps5.isConnected()) {
    delay(100);
    return;
  }

  uint32_t now = millis();
  if (now - lastSend < SEND_INTERVAL_MS) return;
  lastSend = now;

  AnalogPayload payload;
  payload.lx = ps5.LStickX();
  payload.ly = ps5.LStickY();

  bool ok = radio.write(&payload, sizeof(payload));

  if (ok) {
    Serial.printf("[TX] LX=%4d  LY=%4d  ✓\n", payload.lx, payload.ly);
  } else {
    Serial.println("[TX] Send failed (no ACK)");
  }
}