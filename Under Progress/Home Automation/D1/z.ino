#include <ESPmDNS.h>
const char* host = "esp32";
void restart(){ESP.restart();}
void setup()
{
  Serial.begin(115200);
  wifiSetup();
  eepromSetup();
  otaWebSetup();
  alexaSetup();
  reSetup();
  dimmerSetup();
  buttonSetup();
  devicesSetup();
  server.on("/restart", restart);
  server.onNotFound([]() {
    if (!espalexa.handleAlexaApiCall(server.uri(), server.arg(0)))
    {
      server.send(404, "text/plain", "Not found");
    }
  });
  if (!MDNS.begin(host)) { //http://esp32.local
    Dln("mDNS Error");
  }
}
void loop() {
  wifiLoop();
  alexaLoop();
  buttonUpdate();
  writeDevices();
}
