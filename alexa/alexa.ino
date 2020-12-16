/*
 * This code add 5 devices on/off type in alexa on same network.
 * Library Link: https://github.com/Aircoookie/Espalexa
 */
#include <WiFi.h>
#include <Espalexa.h>

const char* ssid = "DRASTI_INSTITUTE";
const char* password = "drasti@1234";
const int R1 = 13;
const int R2 = 26;
const int R3 = 27;
const int R4 = 25;
const int LED = 2;
// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8; //Resolution 8, 10, 12, 15

bool ps1 = LOW;
bool ps2 = LOW;
bool ps3 = LOW;
bool ps4 = LOW;
bool ps5 = LOW;
EspalexaDevice* Dev1;
EspalexaDevice* Dev2;
EspalexaDevice* Dev3;
EspalexaDevice* Dev4;
EspalexaDevice* Dev5;

void connectWifi();
void alexaChanged(EspalexaDevice* dev);
Espalexa espalexa;
void setup()
{
  Serial.begin(115200);
  connectWifi();

  pinMode(LED, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(LED, ledChannel);

  Dev1 = new EspalexaDevice("Dev1", alexaChanged, EspalexaDeviceType::onoff);
  Dev2 = new EspalexaDevice("Dev2", alexaChanged, EspalexaDeviceType::onoff);
  Dev3 = new EspalexaDevice("Dev3", alexaChanged, EspalexaDeviceType::onoff);
  Dev4 = new EspalexaDevice("Dev4", alexaChanged, EspalexaDeviceType::onoff);
  Dev5 = new EspalexaDevice("Dev5", alexaChanged, EspalexaDeviceType::onoff);
  espalexa.addDevice(Dev1);
  espalexa.addDevice(Dev2);
  espalexa.addDevice(Dev3);
  espalexa.addDevice(Dev4);
  espalexa.addDevice(Dev5);
  espalexa.begin();
}
void loop() {
  espalexa.loop();
  delay(1);
}
void alexaChanged(EspalexaDevice* d) {
  if (d == nullptr) return;
  switch (d->getId()) {
    case 0: if (d->getValue()) ps1 = LOW; else ps1 = HIGH; digitalWrite(R1, ps1); break;
    case 1: if (d->getValue()) ps2 = LOW; else ps2 = HIGH; digitalWrite(R2, ps2); break;
    case 2: if (d->getValue()) ps3 = LOW; else ps3 = HIGH; digitalWrite(R3, ps3); break;
    case 3: if (d->getValue()) ps4 = LOW; else ps4 = HIGH; digitalWrite(R4, ps4); break;
    case 4: if (d->getValue()) ps5 = LOW; else ps5 = HIGH; digitalWrite(LED, ps5); break;
    default: break;
  }
}
// connect to wifi – returns true if successful or false if not
void connectWifi() {
  bool state = true;
  int i = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  if (!state) {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
