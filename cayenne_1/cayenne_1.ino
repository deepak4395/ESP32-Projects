//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>

// WiFi network info.
char ssid[] = "DRASTI_INSTITUTE";
char wifiPassword[] = "drasti@1234";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "ca190250-d3ec-11e9-84bb-8f71124cfdfb";
char password[] = "f7e818ed23c091dcfb53ef6bb6a30fd11eea3250";
char clientID[] = "148b87a0-f48f-11e9-b49d-5f4b6757b1bf";
const int R1 = 13;
const int R2 = 26;
const int R3 = 27;
const int R4 = 25;
const int LED = 2;
bool v1 = LOW;
bool v2 = LOW;
bool v3 = LOW;
bool v4 = LOW;

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(LED, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);
}

void loop() {
  Cayenne.loop();
}

CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  switch (request.channel) {
    case 1: if (getValue.asInt())v1 = LOW; else v1 = HIGH; digitalWrite(R1, v1); break;
    case 2: if (getValue.asInt())v2 = LOW; else v2 = HIGH; digitalWrite(R2, v2); break;
    case 3: if (getValue.asInt())v3 = LOW; else v3 = HIGH; digitalWrite(R3, v3); break;
    case 4: if (getValue.asInt())v4 = LOW; else v4 = HIGH; digitalWrite(R4, v4); break;
    default: break;

  }
}
