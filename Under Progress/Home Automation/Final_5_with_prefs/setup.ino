void setup()
{
  Serial.begin(115200);
  connectWifi();
  otaWebSetup();
  alexaSetup();
  reSetup();
  buttonSetup();
 // pwmSetup(LED, 0);
  {
   // nvsSetup();
    devicesSetup();
    dimmerSetup();
  }
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
}
