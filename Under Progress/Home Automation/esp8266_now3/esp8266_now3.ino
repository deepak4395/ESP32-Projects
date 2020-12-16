#include <ESP8266WiFi.h>
#include <WifiEspNow.h>
//16-D0(no pull up,INPUT_PULLDOWN_16 ,BUILTIN-LED ,NO INTERRUPT)
//4-D2,5-D1,14-D5,12-D6,13-D7
//3-RX-D9,1-TX-D10
// Tx creates error in serial moniton when used as input or output.
//#define SwitchOnly
#ifdef SwitchOnly
//For 3 Switch
const int noOfSwitch = 3;
const int R[noOfSwitch] = {5, 14, 4};
const int F[noOfSwitch] = {12, 3, 13};
#define DimmerUp -1
#define DimmerDown -1
#define outputPin -1
#define zerocross -1

#else
// For 1 switch 1 Dimmer
const int noOfSwitch = 1;
const int R[noOfSwitch] = {5};
const int F[noOfSwitch] = {3};
#define DimmerUp 12
#define DimmerDown 13
#define outputPin  14
#define zerocross  4
#endif

//No changes below this;

bool V[noOfSwitch];
int Power;

bool buttonFlag = false;
volatile bool powerFlag = false;

const uint16_t uChipId = ESP.getChipId();
String deviceName;
char *uName;

void string(String s) {
  deviceName = s + "- Drasti-" + String(uChipId, HEX) + " Data-";
  for (int i = 0; i < noOfSwitch; i++) {
    deviceName = deviceName + "bulb" + String(i + 1);
    if (V[i]) deviceName = deviceName + "=OFF;";
    else deviceName = deviceName + "=ON;";
  }
  deviceName = deviceName + "fan1=" + String(Power) + ";#";
  uName = const_cast<char*>(deviceName.c_str());
}

uint8_t serverAddress[6];
bool serverFlag2 = false;

#define Debug
#ifdef Debug
#define D(x) Serial.print(x)
#define Dln(x) Serial.println(x)
#else
#define D(x)
#define Dln(x)
#endif
