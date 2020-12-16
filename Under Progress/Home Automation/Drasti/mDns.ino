#include <ESPmDNS.h>
const char* host = "esp32";
void mDnsSetup() {
  if (!MDNS.begin(host)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
  }
}
