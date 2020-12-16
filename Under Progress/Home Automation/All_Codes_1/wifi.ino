void apMode(bool i) {
  if (i) {
    Dln("Starting Ap Mode");
    WiFi.softAP(softAP_ssid, softAP_password);
    delay(500);
    D("AP IP address: ");
    Dln(WiFi.softAPIP());
  }
  else {
    // close Ap mode
    WiFi.mode(WIFI_STA);
    Dln("Ap Mode Off");
  }
}
bool connectWifi() {
  bool state = true;
  int i = 0;
  Dln("Connecting to WIFI as STA");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    D(".");
    if (i > 10) {
      state = false; break;
    }
    i++;
  }
  Dln();
  if (state) {
    D("Connected to ");
    Dln(ssid);
    D("IP address: ");
    Dln(WiFi.localIP());
  }
  else{
    Dln("Failed");
  }
  return state;
}
