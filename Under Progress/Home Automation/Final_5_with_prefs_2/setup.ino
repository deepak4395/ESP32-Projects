void setup()
{
  Serial.begin(115200);
  connectWifi();
  otaWebSetup();
  alexaSetup();
  reSetup();
  dimmerSetup();
  buttonSetup();
  pwmSetup(LED, 0);
  devicesSetup();
  nvsSetup();
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}
