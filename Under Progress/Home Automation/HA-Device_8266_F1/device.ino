void devicesSetup() {
  for (int i = 0; i < noOfSwitch; i++) {
    pinMode(R[i], OUTPUT);
  }
}
void writeDevices() {
  if (buttonFlag) {
    buttonFlag = false;
    for (int i = 0; i < noOfSwitch; i++) {
      digitalWrite(R[i], V[i]);
      saveDevices(i);
      D(V[i]);
    }
    Dln(Power);
    if (serverFlag2) {
      string("U");
      WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
    }
  }
  if (powerFlag) {
    dimmerSetPower(Power);
    powerFlag = false;
    savePower();
    if (serverFlag2) {
      string("U");
      WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
    }
  }
}
