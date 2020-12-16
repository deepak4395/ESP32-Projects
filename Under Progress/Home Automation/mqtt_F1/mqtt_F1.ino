#include <WiFi.h>

const int noOfSwitch = 4;
const int R[noOfSwitch] = {13, 26, 27, 25};
bool V[noOfSwitch] = {LOW, LOW, LOW, LOW};
String Name[noOfSwitch]={"Light1","Light2","Light3","Light4"};
volatile int16_t Power = 0;

bool buttonFlag = false;
volatile bool powerFlag = false;

// Update these with values suitable for your network.
const char* ssid = "DRASTI_INSTITUTE";
const char* password = "Drasti@4321";
void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
