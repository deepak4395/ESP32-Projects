
int Add[noOfSwitch + 1], address = 0;

void eepromSetup() {
  if (!EEPROM.begin(1000)) {
    delay(1000);
    ESP.restart();
  }

  for (int i = 0; i < noOfSwitch; i++) {
    Add[i] = address;
    address += sizeof(bool);
  }
  Add[noOfSwitch] = address;

  for (int i = 0; i < noOfSwitch; i++) {
    V[i] = EEPROM.readBool(Add[i]);
    digitalWrite(R[i], V[i]);
    Serial.println(V[i]);
  }
  Power = EEPROM.read(50);
  Serial.println(Power);
  dimmerSetPower(Power);
}
void dimmerUpdate() {
  Serial.println("Here");
  EEPROM.write(50, Power);
  EEPROM.commit();
}
void eepromLoop() {
  for (int i = 0; i < noOfSwitch; i++) {
    EEPROM.writeBool(Add[i], V[i]);
  }
  // EEPROM.writeInt(Add[noOfSwitch], Power);
  EEPROM.commit();
}
