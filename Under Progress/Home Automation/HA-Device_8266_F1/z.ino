void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Dln("InSetup");
  for (int i = 0; i < noOfSwitch; i++) {
    V[i] = LOW;
    Time[i] = millis();
    px[i] = 1;
  }
  eepromSetup();
  dimmerSetup();
  buttonSetup();
  devicesSetup();
  nowSetup();
  Serial.println("Setup Done");
}

void loop() {
  nowLoop();
  buttonUpdate();
  writeDevices();
}
