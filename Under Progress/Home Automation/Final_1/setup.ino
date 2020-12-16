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
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);
  dimmerSetPower(95);
}
