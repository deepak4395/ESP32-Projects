void setup() {
  Serial.begin(115200);
  if (connectWifi()) {
    if (pingRemote()) mqttSetup();
  }
  else {
    
  }
  apMode(true);
  //eepromSetup();
  { reSetup();
    dimmerSetup();
    buttonSetup();
    devicesSetup();
  }
}

void loop() {
  mqttLoop();
  { buttonUpdate();
    writeDevices();
  }
}
