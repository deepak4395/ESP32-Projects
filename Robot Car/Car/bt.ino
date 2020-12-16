#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
void btloop() {
  if (!espNowFlag) {
    if (SerialBT.available()) {
      char c = SerialBT.read();
      Serial.println(c);
      if (c == 'F') {
        carMovement = "forward";
      }
      if (c == 'B') {
        carMovement = "backward";
      }
      if (c == 'L') {
        carMovement = "left";
      }
      if (c == 'R') {
        carMovement = "right";
      }
      if (c == 'S') {
        carMovement = "stop";
      }
      if (c >= 48 && c <= 57) {
        int i = c;
        carSpeed = map(i - 48, 0, 9, 130, 250);
      }
      updateCar();
    }
  }
}
