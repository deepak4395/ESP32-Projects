#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
const int R1 = 13;
const int R2 = 26;
const int R3 = 27;
const int R4 = 25;
const int LED = 2;
int z;
BluetoothSerial SerialBT;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);

  Serial.begin(115200);
  SerialBT.begin("DRASTI"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void updateDevices(int y) {
  if ( z != y) {
    z = y;
    switch (z) {
      case 1: digitalWrite(R1, LOW); break;
      case 2: digitalWrite(R1, HIGH); break;
      case 3: digitalWrite(R2, LOW); break;
      case 4: digitalWrite(R2, HIGH); break;
      case 5: digitalWrite(R3, LOW); break;
      case 6: digitalWrite(R3, HIGH); break;
      case 7: digitalWrite(R4, LOW); break;
      case 8: digitalWrite(R4, HIGH); break;
      case 9: digitalWrite(LED, LOW); break;
      case 10: digitalWrite(LED, HIGH); break;
      case 11: digitalWrite(R1, LOW); digitalWrite(R2, LOW); digitalWrite(R3, LOW); digitalWrite(R4, LOW); digitalWrite(LED, LOW); break;
      case 12: digitalWrite(R1, HIGH); digitalWrite(R2, HIGH); digitalWrite(R3, HIGH); digitalWrite(R4, HIGH); digitalWrite(LED, HIGH); break;
    }
  }
}
void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    String d = SerialBT.readString();
    int x = d.toInt();
    updateDevices(x);
    Serial.println(x);
  }
  delay(20);
}
