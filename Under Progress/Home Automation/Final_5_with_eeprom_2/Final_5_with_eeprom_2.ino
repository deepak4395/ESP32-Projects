
const int noOfSwitch = 4;
const int R[noOfSwitch] = {13, 26, 27, 25};
bool V[noOfSwitch] = {LOW, LOW, LOW, LOW};
int Power = 0;

int16_t encoder = 0;

char reason = ' ';
const int LED = 2;

#include <Espalexa.h>
#include "EEPROM.h"

String Name[noOfSwitch] = {"Light1", "Light2", "Light3", "Light4"};

EspalexaDevice* Dev[noOfSwitch];
EspalexaDevice* Dev5;
Espalexa espalexa;
WebServer server(80);

void alexaChanged(EspalexaDevice* d) {
  if (d == nullptr) return;
  reason = 'a';
  int i = d->getId();
  if (i < noOfSwitch) {
    if (d->getValue()) V[i] = LOW;
    else V[i] = HIGH;
    statusUpdate(reason, i);
  }
  else {
    Power = d->getPercent();
    encoder = map(Power, 0, 100, 0, 40);
    dimmerUpdate();
    dimmerSetPower(Power); // 0 - 97 not 0 to 100 flicker at 98 to 100
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
