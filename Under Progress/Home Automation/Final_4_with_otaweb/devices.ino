void devicesSetup() {
  for (int i = 0; i < noOfSwitch; i++) {
    pinMode(R[i], OUTPUT);
    digitalWrite(R[i], LOW);
  }
}
