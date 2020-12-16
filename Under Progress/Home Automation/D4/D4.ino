#define ESPALEXA_DEBUG
#include <Espalexa.h>

const int noOfSwitch = 4;
const int R[noOfSwitch] = {13, 26, 27, 25};
bool V[noOfSwitch] = {LOW, LOW, LOW, LOW};
String Name[noOfSwitch]={"Light1","Light2","Light3","Light4"};
volatile int16_t Power = 0;

bool buttonFlag = false;
volatile bool powerFlag = false;

const char *softAP_ssid = "ESP_ap";
const char *softAP_password = "12345678";

char ssid[32] = "";
char password[32] = "";
IPAddress apIP;

#define Debug
#ifdef Debug
#define D(x) Serial.print(x)
#define Dln(x) Serial.println(x)
#else
#define D(x)
#define Dln(x)
#endif

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
    buttonFlag = true;
  }
  else {
    Power = d->getPercent();
    powerFlag = true;
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
