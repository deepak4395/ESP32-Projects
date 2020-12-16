#include <ESPmDNS.h>
const char* host = "esp32";
void restart() {
  ESP.restart();
  server.client().stop();
}
void handleRoot() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", "");
  server.sendContent(
    "<html><head></head><body>"
    "<h1>Smart Home By Drasti</h1>"
  );
  if (server.client().localIP() == apIP) {
    server.sendContent(String("<p>You are connected through the soft AP: ") + softAP_ssid + "</p>");
    server.sendContent("<p><a href='/wifi'>Config the wifi connection</a> for alexa and remote acess features .</p>");
  } else {
    server.sendContent(String("<p>You are connected through the wifi network: ") + ssid + "</p>");
  }
  server.sendContent(
    "<p>You may want to <a href='/wifi'>config the wifi connection</a>.</p>"
    "<p>You may want to <a href='/restart'>Restart</a>.</p>"
    "</body></html>"
  );
  server.sendContent(SendHTML());
  server.client().stop();
}

void serverSetup() {
  server.on("/", handleRoot);
  server.on("/devices/{}/value/{}", []() {
    int device = server.pathArg(0).toInt();
    int value = server.pathArg(1).toInt();
    if (value == 1)V[device] = true; else V[device] = false;
    buttonFlag = true;
    server.sendHeader("Location", "/");
    server.send(303);
    server.client().stop();
  });
  server.on("/restart", restart);
  server.onNotFound([]() {
    if (!espalexa.handleAlexaApiCall(server.uri(), server.arg(0)))
    {
      server.send(404, "text/plain", "Not found");
    }
  });
}
void setup()
{
  Serial.begin(115200);
  wifiSetup();
  eepromSetup();
  otaWebSetup();
  serverSetup();
  alexaSetup();
  reSetup();
  dimmerSetup();
  buttonSetup();
  devicesSetup();

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
