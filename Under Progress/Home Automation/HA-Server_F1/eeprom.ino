#include "EEPROM.h"
#define EEPROM_SIZE 400

void eepromSetup() {
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM");
  }
}
void eepromSaveDevice(int i) {
  EEPROM.writeByte(0, f + 1);
  EEPROM.writeBytes((5 + (7 * f)), mac1[i], 6);
  EEPROM.commit();
}

void eepromLoad() {
  f = EEPROM.readByte(0);
  if (f < 22) {
    for (int i = 0; i < f; i++) {
      EEPROM.readBytes((5 + (7 * i)), mac1[i], 6);
      for (int j = 0; j < 6; j++) {
        Serial.printf("%02X", mac1[i][j]);
        if (j < 5)Serial.print(":");
      }
      Serial.println();
    }
  }
  else f = 0;
  Serial.println(f);
}
