#include <EEPROM.h>
int Add[noOfSwitch + 1], address = 0;

void eepromSetup() {
  EEPROM.begin(512);
  for (int i = 0; i < noOfSwitch; i++) {
    Add[i] = address;
    address += sizeof(bool);
  }
  Add[noOfSwitch] = address;
  address += sizeof(int);  
  buttonFlag = true;
  powerFlag = true;
  for (int i = 0; i < noOfSwitch; i++) {
    V[i] = EEPROM.read(Add[i]);
  }
  Power = EEPROM.read(Add[noOfSwitch]);
}
void saveDevices(int i) {
  EEPROM.write(Add[i], V[i]);
  EEPROM.commit();
}
void savePower() {
  EEPROM.write(Add[noOfSwitch], Power);
  EEPROM.commit();
}
void saveServer(){
  
}
