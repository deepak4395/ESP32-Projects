#include <WifiEspNow.h>
const uint16_t uChipId = ESP.getChipId();
String deviceName;
char *uName;
String handPosition = "default",carMovement = "default", carMovementP = "default";
int carSpeed = 180;
void string(String s) {
  deviceName = s + "- Ritika-" + String(uChipId, HEX) + " Data-";
  deviceName = deviceName + carMovement + ";#";
  uName = const_cast<char*>(deviceName.c_str());
}
uint8_t serverAddress[6];
bool serverFlag2 = false;
bool serverFlag = false;
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
char* bmesg = "B- Hello Code";
bool ok;
void testController() {
  carMovement = String("forward;speed=") + String(carSpeed);
  string("U");
  WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
  delay(5000);
  carMovement = String("backward;speed=") + String(carSpeed);
  string("U");
  WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
  delay(5000);
  carMovement = String("left;speed=") + String(carSpeed);
  string("U");
  WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
  delay(5000);
  carMovement = String("right;speed=") + String(carSpeed);
  string("U");
  WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
  delay(5000);
  carMovement = String("stop;speed=") + String(0);
  string("U");
  WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
  delay(5000);
}
void process(String s) {
  Serial.println(s);
  if (s == "ServerCode") {
    WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
    //sendMesg("Server", serverAddress, uName);
  }
}

void onReceiveData(const uint8_t mac[6], const uint8_t* buf, size_t count, void* cbarg) {
  Serial.printf("Message from %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  String s;
  for (int i = 0; i < count; i++) s = s + (char)buf[i];
  Serial.println(s);

  if (!serverFlag2) {
    if (s == "ServerCode") {
      serverFlag = true;
      memcpy(serverAddress, mac, 6);
    }
  }
  else {
    if (!memcmp(serverAddress, mac, 6)) {
      process(s);
    }
  }
}

void nowSetup() {
  WiFi.persistent(false);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESPNOW", nullptr, 3);
  WiFi.softAPdisconnect(false);
  Serial.println(WiFi.softAPmacAddress());
  ok = WifiEspNow.begin();
  if (!ok) {
    Serial.println("WifiEspNow.begin() failed");
    ESP.restart();
  }
  WifiEspNow.onReceive(onReceiveData, nullptr);
  ok = WifiEspNow.addPeer(broadcastAddress);
  if (!ok) {
    Serial.println("WifiEspNow.addPeer() failed");
  }
}

int bTime = millis();
void nowLoop() {
  if (!serverFlag2 && (millis() - bTime > 1000)) {
    Serial.println("Sent Broadcast");
    bTime = millis();
    WifiEspNow.send(broadcastAddress, reinterpret_cast<const uint8_t*>(bmesg), strlen(bmesg));
  }
  if (serverFlag) {
    serverFlag = false;
    ok = WifiEspNow.addPeer(serverAddress);
    if (ok) {
      Serial.println("WifiEspNow.addPeer() Success");
      serverFlag2 = true;
    }
    if (serverFlag2) {
      string("A");
      WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
    }
  }
  //testController();
}
