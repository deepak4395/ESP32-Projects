void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(onReceiveData);
  wifiSetup();
  eepromSetup();
  eepromLoad();
  int i=f;
  while (i > 0) {
    i=i-1;
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, mac1[i], 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    bool exists = esp_now_is_peer_exist(peerInfo.peer_addr);
    if (exists) {
      Serial.println("Already Paired");
    } else {
      esp_err_t addStatus = esp_now_add_peer(&peerInfo);
      if (addStatus == ESP_OK) {
        Serial.println("Pair success");
      } else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
        Serial.println("ESPNOW Not Init");
      } else if (addStatus == ESP_ERR_ESPNOW_ARG) {
        Serial.println("Add Peer - Invalid Argument");
      } else if (addStatus == ESP_ERR_ESPNOW_FULL) {
        Serial.println("Peer list full");
      } else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
        Serial.println("Out of memory");
      } else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
        Serial.println("Peer Exists");
      } else {
        Serial.println("Not sure what happened");
      }
    }
    sendMesg(i, sC);
  }
  if (f > 0) {
    for (int i = 0; i < f; i++) {
    }
  }
}

void loop() {
  if (addFlag) {
    addFlag = false;
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, mac1[f], 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    bool exists = esp_now_is_peer_exist(peerInfo.peer_addr);
    if (exists) {
      Serial.println("Already Paired");
    } else {
      esp_err_t addStatus = esp_now_add_peer(&peerInfo);
      if (addStatus == ESP_OK) {
        Serial.println("Pair success");
      } else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
        Serial.println("ESPNOW Not Init");
      } else if (addStatus == ESP_ERR_ESPNOW_ARG) {
        Serial.println("Add Peer - Invalid Argument");
      } else if (addStatus == ESP_ERR_ESPNOW_FULL) {
        Serial.println("Peer list full");
      } else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
        Serial.println("Out of memory");
      } else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
        Serial.println("Peer Exists");
      } else {
        Serial.println("Not sure what happened");
      }
    }
    bool b = sendMesg(f, sC);

    if (b) {
      eepromSaveDevice(f);
      if (f < noOfDevice)f++;
      else Serial.println("Error Max Devices Added");
    }
    Serial.print("No of Device(s)- ");
    Serial.println(f);
  }
  wifiLoop();
}
