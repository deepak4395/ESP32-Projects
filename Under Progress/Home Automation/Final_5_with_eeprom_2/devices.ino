void devicesSetup() {
  for (int i = 0; i < noOfSwitch; i++) {
    pinMode(R[i], OUTPUT);
    //digitalWrite(R[i], LOW);
  }
}

void statusUpdate(char x, int i) {
  if (reason == 'a') {
    digitalWrite(R[i], V[i]);
    reason = ' ';
  }
  if (reason == 'b') {
    if (V[i]) Dev[i]->setValue(0); else Dev[i]->setValue(255);
    digitalWrite(R[i], V[i]);
  }
  EEPROM.writeBool(Add[i], V[i]);
  EEPROM.commit();
}
