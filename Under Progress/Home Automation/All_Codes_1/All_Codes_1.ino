#include <WiFi.h>

const int noOfSwitch = 4;
const int R[noOfSwitch] = {13, 26, 27, 25};
bool V[noOfSwitch] = {LOW, LOW, LOW, LOW};
String Name[noOfSwitch]={"Light1","Light2","Light3","Light4"};

volatile int16_t Power = 0;

bool buttonFlag = false;
volatile bool powerFlag = false;

uint16_t uChipId = ESP.getEfuseMac();
const String deviceName = "Drasti " + String(uChipId, HEX);

const char *softAP_ssid = const_cast<char*>(deviceName.c_str());
const char *softAP_password = "12345678";

char ssid[32] = "DRASTI_INSTITUTE";
char password[32] = "Drasti@4321";

#define Debug
#ifdef Debug
#define D(x) Serial.print(x)
#define Dln(x) Serial.println(x)
#else
#define D(x)
#define Dln(x)
#endif
