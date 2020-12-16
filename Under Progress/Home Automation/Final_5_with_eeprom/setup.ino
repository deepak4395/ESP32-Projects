void setup()
{
  Serial.begin(115200);
  connectWifi();
  otaWebSetup();
  alexaSetup();
  reSetup();
  devicesSetup();
  
  dimmerSetup();
  buttonSetup();
  pwmSetup(LED, 0);
 // eepromSetup();
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}
