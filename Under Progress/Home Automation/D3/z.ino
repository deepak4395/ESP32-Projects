#include <ESPmDNS.h>
const char* host = "esp32";
int resetPin = 0;
int TimeZero = millis();
bool resetCheck() {
  if (digitalRead(F[resetPin])) {
    TimeZero = millis();
  }
  else {
    if (millis() - TimeZero > 5000) {
      return true;
    }
  }
  return false;
}
void reset() {
  preferences.clear();
  restart();
}
void setup()
{
  Serial.begin(115200);
  wifiSetup();
  eepromSetup();
  otaWebSetup();
  serverSetup();
  alexaSetup();
  {
    reSetup();
    dimmerSetup();
    buttonSetup();
    devicesSetup();
  }
  if (!MDNS.begin(host)) { //http://esp32.local
    Dln("mDNS Error");
  }
}
void loop() {
  wifiLoop();
  alexaLoop();
  buttonUpdate();
  writeDevices();
  if (resetCheck()) reset();
}
