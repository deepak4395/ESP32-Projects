//BE:DD:C2:63:FE:54
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}
int ledPin = 2;
WiFiServer server(80);
String responseMsg;
void wifiSetup()
{
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("ESP_DRASTI", "123456789") ? "Ready" : "Failed!");
  server.begin();
  Serial.println("Server started");
  pinMode(ledPin, OUTPUT);
}
void wifiLoop()
{
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  String request;
  while (client.available()) {
    char c = client.read();
    request += c;
  }
  Serial.println(request);
  client.flush();

  if (request.indexOf("/CONNECTION=VERIFY") != -1) {
    Serial.println("ESP_DRASTI-CONNECTED-VERIFIED");
    responseMsg = "VERIFIED;bulb=3;fan=2;";
    Serial.println(responseMsg);
  }
  if (request.indexOf("/CONNECTION=ESP-DEVICE-STATUS") != -1) {
    Serial.println("ESP_DRASTI-DEVICE-STATUS");
    String s;
    for (int i = 0; i < f; i++) s = s + deviceValue[i];
    responseMsg = s;
    Serial.println(responseMsg);
  }
  if (request.indexOf("/CONNECTION=update*") != -1) {
    char c = (request.charAt(request.indexOf("Device-") + 7));
    int dU = atoi(&c);
    String mesg = request.substring(request.indexOf("update*") + 7, request.indexOf("**"));
    char *mesg1 = const_cast<char*>(mesg.c_str());
    if (sendMesg(dU - 1, mesg1)) responseMsg = "Updated";
    else responseMsg = "Failed";
    Serial.println(responseMsg);
  }
  if (request.indexOf("/AddDevice") != -1) {
    String s = request.substring(request.indexOf("ice=") + 4, request.indexOf("**"));
    char *macR = const_cast<char*>(s.c_str());
    uint8_t mac_addr2[6];
    int mac_addr[6];
    if (6 == sscanf(macR, "%x:%x:%x:%x:%x:%x%*c",
                    &mac_addr[0],
                    &mac_addr[1],
                    &mac_addr[2],
                    &mac_addr[3],
                    &mac_addr[4],
                    &mac_addr[5]))
    {
      for (int i = 0; i < 6; i++) {
        mac_addr2[i] = (uint8_t)mac_addr[i];
      }
    }
    bool added = false;
    for (int i = 0; i < f; i++) {
      if (!memcmp(mac1[i], mac_addr2, 6)) {
        added = true;
        break;
      }
    }
    if (added) responseMsg = "Already Added";
    else {
      memcpy(mac1[f], mac_addr2, 6);
      addFlag = true;
      responseMsg = "Device Added";
    }
  }
  if (request.indexOf("/homenetwork") != -1) {
    String ssid = request.substring(request.indexOf("id=") + 3, request.indexOf(";p"));
    String password = request.substring(request.indexOf("rd=") + 3, request.indexOf(";;"));
    bool state = true;
    int i = 0;
    Serial.println(ssid);
    Serial.println(password);
    char *s = const_cast<char*>(ssid.c_str());
    char *p = const_cast<char*>(password.c_str());
    WiFi.begin(s, p);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if (i > 10) {
        state = false; break;
      }
      i++;
    }
    if (state) {
      //WiFi.mode(WIFI_STA);
      Serial.print("Connected to ");
      Serial.println(s);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      responseMsg = "HOME_NETWORK;ip=" + toStringIp(WiFi.localIP()) + ";";
    }
    else {
      Serial.println("unable to connect");
      responseMsg = "Unable to connect";
    }
    Serial.println(responseMsg);
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<html><body>");
  client.println("Connection" + responseMsg + "<br/>");
  client.println("</body></html>");
  delay(1);
  Serial.println("Client disconnected");
}
