
const int noOfSwitch = 4;
const int R[noOfSwitch] = {13, 26, 27, 25};
bool V[noOfSwitch] = {LOW, LOW, LOW, LOW};
String Name[noOfSwitch] = {"Light1", "Light2", "Light3", "Light4"};
int16_t Power = 0;
char ssid[32] = "";
char password[32] = "";
bool Reboot = false; 
IPAddress IP;

#include <Espalexa.h>
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
  }
  else {
    Power = d->getPercent();
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
