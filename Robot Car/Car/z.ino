void setup() {
  Serial.begin(115200);
  Dln("Setup Started");
  SerialBT.begin("Riti-Car");
  for (int i = 0; i < 4; i++) {
    ledcSetup(i, 5000, 8);
    ledcAttachPin(motorPin[i], i);
  }
  pinMode(connectionLed, OUTPUT);
  //Esp-Now Setup
  WiFi.mode(WIFI_STA);
  D("Car Mac Address - ");
  Dln(WiFi.macAddress());
  if (esp_now_init() != ESP_OK) {
    Dln("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(onReceiveData);
  digitalWrite(connectionLed, LOW);
  //testCar();
  Dln("Setup Ended");
}

void loop() {
  if (addFlag) {
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, mac1, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    bool exists = esp_now_is_peer_exist(peerInfo.peer_addr);
    if (exists) {
      Dln("Already Paired");
      addFlag = false;
      digitalWrite(connectionLed, HIGH);
      espNowFlag=true;
    } else {
      esp_err_t addStatus = esp_now_add_peer(&peerInfo);
      if (addStatus == ESP_OK) {
        Dln("Pair success");
        addFlag = false;
        digitalWrite(connectionLed, HIGH);
        espNowFlag=true;
      } else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
        Dln("ESPNOW Not Init");
      } else if (addStatus == ESP_ERR_ESPNOW_ARG) {
        Dln("Add Peer - Invalid Argument");
      } else if (addStatus == ESP_ERR_ESPNOW_FULL) {
        Dln("Peer list full");
      } else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
        Dln("Out of memory");
      } else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
        Dln("Peer Exists");
      } else {
        Dln("Not sure what happened");
      }
    }
    bool b = sendMesg(sC);
  }
  btloop();
}
