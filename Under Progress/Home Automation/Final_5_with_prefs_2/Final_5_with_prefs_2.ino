#include "Arduino.h"
#include <Espalexa.h>
#include <WebServer.h>

const int noOfSwitch = 4;
const char R[noOfSwitch] = {13, 26, 27, 25};
bool V[noOfSwitch] = {LOW, LOW, LOW, LOW};
String Name[noOfSwitch]={"Light1","Light2","Light3","Light4"};
const int LED = 2;
int16_t encoder = 0,Power = 0;

EspalexaDevice* Dev[noOfSwitch];
EspalexaDevice* Dev5;
Espalexa espalexa;
WebServer server(80);
void alexaChanged(EspalexaDevice* d) {
  if (d == nullptr) return;
  int i = d->getId();
  if (i < noOfSwitch) {
    if (d->getValue()) V[i] = LOW;
    else V[i] = HIGH;
    digitalWrite(R[i], V[i]);
    saveLoad(i);
  }
  else {
    Power = d->getPercent();
    encoder = map(Power, 0, 100, 0, 40);
    dimmerSetPower(Power); // 0 - 97 not 0 to 100 flicker at 98 to 100
    saveLoad(4);
  }
}
void alexaSetup() {
  for (int i = 0; i < noOfSwitch; i++) {
    Dev[i] = new EspalexaDevice(Name[i], alexaChanged, EspalexaDeviceType::onoff);
    espalexa.addDevice(Dev[i]);
    Dev[i]->setValue(255);
  }
  Dev5 = new EspalexaDevice("Light5", alexaChanged, EspalexaDeviceType::dimmable);
  espalexa.addDevice(Dev5);
  Dev5->setValue(255);
  espalexa.begin(&server);
}
void alexaLoop() {
  espalexa.loop();
}
