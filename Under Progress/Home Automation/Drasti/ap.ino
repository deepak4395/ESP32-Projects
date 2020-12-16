#include <WiFiAP.h>

const char *ap = "ESP32";
const char *apPassword = "yourPassword";

void apModeStart() {
  Serial.println("Configuring access point...");
  WiFi.softAP(ap, apPassword);
  IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

void connectWifi() {
  Serial.println("Connecting as wifi client...");
  WiFi.disconnect();
  WiFi.begin ( ssid, password );
  int connRes = WiFi.waitForConnectResult();
  Serial.print ( "connRes: " );
  Serial.println ( connRes );
}
