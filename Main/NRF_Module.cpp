#include "NRF_Module.h"
#include <SPI.h>
#include <RF24.h>

static RF24* radio = nullptr;
static const byte ADDRESS[6] = "PS5TX";

bool initRadio(uint16_t cePin, uint16_t csnPin) {
  radio = new RF24(cePin, csnPin);

  if (!radio->begin()) {
    return false; 
  }

  radio->setPALevel(RF24_PA_LOW);
  radio->setDataRate(RF24_250KBPS);
  radio->setChannel(108);
  
  radio->setAutoAck(true); 

  radio->openReadingPipe(1, ADDRESS);
  radio->startListening();

  return true;
}

bool checkRadioData(AnalogPayload &payload) {
  if (radio != nullptr && radio->available()) {
    radio->read(&payload, sizeof(payload));
    return true; 
  }
  return false; 
}