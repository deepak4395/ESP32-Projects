bool serverFlag = false;
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
char* bmesg = "B- Hello Code";
bool ok;

void process(String s) {
  Serial.println(s);
  if (s == "S***S") {
    WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
    //sendMesg("Server", serverAddress, uName);
  }
  if (s.indexOf("bulb") != -1) {
    char c = s.charAt(s.indexOf("bulb") + 4);
    int i = atoi(&c);
    if (s.substring(s.indexOf("-O") + 2) == "N") V[i - 1] = false;
    else V[i - 1] = true;
    buttonFlag = true;
  }
  else if (s.indexOf("fan") != -1) {

  }
}

void onReceiveData(const uint8_t mac[6], const uint8_t* buf, size_t count, void* cbarg) {
  Serial.printf("Message from %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  String s;
  for (int i = 0; i < count; i++) s = s + (char)buf[i];
  Serial.println(s);

  if (!serverFlag2) {
    if (s == "S***S") {
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
  if (!serverFlag2 && (millis() - bTime > 10000)) {
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
      saveServer();
    }
  }
}
