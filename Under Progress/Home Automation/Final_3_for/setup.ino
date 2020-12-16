void setup()
{
  Serial.begin(115200);
  connectWifi();
  // otaWebSetup();
  alexaSetup();
  reSetup();
  dimmerSetup();
  buttonSetup();
  pwmSetup(LED, 0);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  for (int i = 0; i < noOfSwitch; i++) {
    pinMode(R[i], OUTPUT);
    digitalWrite(R[i], LOW);
  }
  dimmerSetPower(95);
}
