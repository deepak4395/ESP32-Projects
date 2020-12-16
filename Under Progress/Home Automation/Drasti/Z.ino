
void setup() {
  Serial.begin(115200);
  nvsSetup();
  loadCredentials();
  loadReboot();
  connectWifi;
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println ( "" );
    Serial.print ( "Connected to " );
    Serial.println ( ssid );
    Serial.print ( "IP address: " );
    Serial.println ( WiFi.localIP() );
  }
  else {
    apModeStart();
  }
  serverSetup();
  otaWebSetup();
  alexaSetup();
  //  reSetup(); //
  //  dimmerSetup();//
  //  devicesSetup();//
  //  buttonSetup(); //
}

void loop() {
  espalexa.loop();
  // buttonLoop();
  // if(resetCheck()) reboot();
}
