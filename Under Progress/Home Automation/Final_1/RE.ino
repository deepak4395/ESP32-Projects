#include "AiEsp32RotaryEncoder.h"

#define ROTARY_ENCODER_A_PIN 21
#define ROTARY_ENCODER_B_PIN 22
#define ROTARY_ENCODER_BUTTON_PIN 23
#define ROTARY_ENCODER_VCC_PIN -1 /*put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN);

void reSetup() {
  rotaryEncoder.begin();
  rotaryEncoder.setup([] {rotaryEncoder.readEncoder_ISR();});
  rotaryEncoder.setBoundaries(0, 42, false ); //minValue, maxValue, cycle values (when max go to min and vice versa)
}

void reLoop() {
  if (rotaryEncoder.reFlag) {
    Serial.println(rotaryEncoder.encoder);
    Power = rotaryEncoder.steps;
    dimmerSetPower(Power); // 0 - 97 not 0 to 100 flicker at 98 to 100
    Dev5->setPercent(Power);
    rotaryEncoder.reFlag = false;
  }
}
