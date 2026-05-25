#ifndef NRF_MODULE_H
#define NRF_MODULE_H

#include <Arduino.h>

struct AnalogPayload {
  int8_t lx;
  int8_t ly;
};

// Function declarations
bool initRadio(uint16_t cePin, uint16_t csnPin);
bool checkRadioData(AnalogPayload &payload);

#endif // RADIO_RECEIVER_H