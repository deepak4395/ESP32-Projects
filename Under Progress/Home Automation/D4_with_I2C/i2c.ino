#include <Wire.h>

//#define B
#ifdef B
#define D(x) 
#define Dln(x)
#else
#define D(x) Serial.print(x)
#define Dln(x) Serial.println(x)
#endif
int nDevices = 0;
byte *Slave=(uint8_t *)malloc(sizeof(uint8_t));
const byte addressCommon = 119;
byte last = 64;

void check() {
  byte error = 0;
  while (error == 0) {
    Wire.beginTransmission(addressCommon);
    error = Wire.endTransmission();
    if (error == 0) {
      Wire.beginTransmission(addressCommon);
      Wire.write("Message, Your NewAdd:");
      last = last + 1;
      Slave[nDevices] = last;
      nDevices++;
      Wire.write(last);
      Wire.endTransmission();
    }
    else if (error == 4) {
      D("Unknow error at address ");
      Dln(addressCommon);
    }
    delay(1000);
  }
  D("Found ");
  D(nDevices);
  Dln(" Slaves");
}

void request() {
  Dln("Message from Slaves");
  for (int i = 0; i < nDevices; i++) {
    D("Device ");
    D(i + 1);
    D(" Message: ");
    Wire.requestFrom(Slave[i], 13); 
    while (Wire.available())
    {
      char c = Wire.read(); 
      D(c);
    }
    Dln();
  }
}
void i2cSetup()
{
  Serial.begin(115200);
  Wire.begin();
  pinMode(4, OUTPUT);
  Dln("Finding Slaves");
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  delay(1000);
  check();
}

void i2cLoop()
{
  if (nDevices > 0)
  {
    request();
    delay(3000);
  }
}
