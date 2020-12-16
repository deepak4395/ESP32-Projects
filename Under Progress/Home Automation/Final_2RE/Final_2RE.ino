#include "Arduino.h"
#include <Espalexa.h>

EspalexaDevice* Dev1;
EspalexaDevice* Dev2;
EspalexaDevice* Dev3;
EspalexaDevice* Dev4;
EspalexaDevice* Dev5;

Espalexa espalexa;
const int R1 = 13;
const int R2 = 26;
const int R3 = 27;
const int R4 = 25;
const int LED = 2;
bool V1 = LOW;
bool V2 = LOW;
bool V3 = LOW;
bool V4 = LOW;
int Power = 0;

void alexaChanged(EspalexaDevice* d) {
  if (d == nullptr) return;
  switch (d->getId()) {
    case 0: if (d->getValue()) V1 = LOW; else V1 = HIGH; digitalWrite(R1, V1); break;
    case 1: if (d->getValue()) V2 = LOW; else V2 = HIGH; digitalWrite(R2, V2); break;
    case 2: if (d->getValue()) V3 = LOW; else V3 = HIGH; digitalWrite(R3, V3); break;
    case 3: if (d->getValue()) V4 = LOW; else V4 = HIGH; digitalWrite(R4, V4); break;
    case 4: Power = d->getPercent();
      //  rotaryEncoder.encoder = map(Power, 0, 100, 0, 40);
      dimmerSetPower(Power); // 0 - 97 not 0 to 100 flicker at 98 to 100
      break;
    default: break;
  }
}

void alexaSetup() {
  Dev1 = new EspalexaDevice("Light 1", alexaChanged, EspalexaDeviceType::onoff);
  Dev2 = new EspalexaDevice("Light 2", alexaChanged, EspalexaDeviceType::onoff);
  Dev3 = new EspalexaDevice("Light 3", alexaChanged, EspalexaDeviceType::onoff);
  Dev4 = new EspalexaDevice("Light 4", alexaChanged, EspalexaDeviceType::onoff);
  Dev5 = new EspalexaDevice("Light 5", alexaChanged, EspalexaDeviceType::dimmable);
  espalexa.addDevice(Dev1);
  espalexa.addDevice(Dev2);
  espalexa.addDevice(Dev3);
  espalexa.addDevice(Dev4);
  espalexa.addDevice(Dev5);
  Dev1->setValue(255);
  Dev2->setValue(255);
  Dev3->setValue(255);
  Dev4->setValue(255);
  Dev5->setValue(255);
  espalexa.begin();
}

void alexaLoop() {
  espalexa.loop();
}
