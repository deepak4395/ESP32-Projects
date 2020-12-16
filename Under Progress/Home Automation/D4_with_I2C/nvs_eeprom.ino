#include "EEPROM.h"
int Add[noOfSwitch + 1], address = 0;

void eepromSetup() {
  if (!EEPROM.begin(512)) {
    Dln("EEPROM Error");
  }
  for (int i = 0; i < noOfSwitch; i++) {
    Add[i] = address;
    address += sizeof(bool);
  }
  Add[noOfSwitch] = address;
  buttonFlag = true;
  powerFlag = true;
  for (int i = 0; i < noOfSwitch; i++) {
    V[i] = EEPROM.readBool(Add[i]);
  }
  Power = EEPROM.readInt(Add[noOfSwitch]);
}
void saveDevices(int i) {
  EEPROM.writeBool(Add[i], V[i]);
  EEPROM.commit();
}
void savePower(int P) {
  EEPROM.writeInt(Add[noOfSwitch], Power);
  EEPROM.commit();
}

#include <Preferences.h>
Preferences preferences;
void nvsSetup(){
  preferences.begin("Wifi Networks", false);
}
void loadCredentials() {
  preferences.getString("ssid", ssid, sizeof(ssid));
  preferences.getString("password", password, sizeof(password));
}

/** Store WLAN credentials to Preference */
void saveCredentials() {
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
}
