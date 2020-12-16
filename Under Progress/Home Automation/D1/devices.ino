void devicesSetup() {
  for (int i = 0; i < noOfSwitch; i++) {
    pinMode(R[i], OUTPUT);
  }
}
void writeDevices() {
  if (buttonFlag) {
    buttonFlag = false;
    for (int i = 0; i < noOfSwitch; i++) {
      if (V[i]) Dev[i]->setValue(0); else Dev[i]->setValue(255);
      digitalWrite(R[i], V[i]);
      saveDevices(i);
      D(V[i]);
    }
    Dln(Power);
  }
  if (powerFlag) {
    dimmerSetPower(Power);
    Dev5->setPercent(Power);
    powerFlag = false;
    savePower(Power);
  }
}
