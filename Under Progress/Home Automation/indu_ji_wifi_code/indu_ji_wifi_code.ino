#include <WiFi.h>
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}
int ledPin = 2; // GPIO13 or for NodeMCU you can directly write D7
WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.
String responseMsg;
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("ESP_DRASTI", "123456789") ? "Ready" : "Failed!");
  server.begin();
  Serial.println("Server started");
}
void loop()
{
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
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

  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
  if (request.indexOf("/CONNECTION=VERIFY") != -1) {
    Serial.println("ESP_DRASTI-CONNECTED-VERIFIED");
    responseMsg = "VERIFIED;bulb=3;fan=2;";
    Serial.println(responseMsg);
  }
  if (request.indexOf("/CONNECTION=DEVICE-STATUS") != -1) {
    Serial.println("ESP_DRASTI-DEVICE-STATUS");
    responseMsg = "DEVICE-STATUS;bulb1=ON;bulb2=OFF;bulb3=ON;fan1=OFF;fan2=ON;";
    Serial.println(responseMsg);
  }
  if (request.indexOf("/CONNECTION=ESP-DEVICE-STATUS") != -1) {
    Serial.println("ESP_DRASTI-DEVICE-STATUS");
    responseMsg = "Device-1;bulb1=ON;bulb2=OFF;fan1=OFF;fan2=ON;#Device-2;bulb1=ON;fan1=OFF;fan2=ON#Device-3;bulb1=ON;fan1=OFF;#";
    Serial.println(responseMsg);
  }
  if (request.indexOf("/homenetwork") != -1) {
    Serial.println(request);
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
      Serial.println(responseMsg);
    }
    else {
      Serial.println("unable to connect");
    }
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  //client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("Connection" + responseMsg + "<br/>");
  client.print("Led pin is now: ");

  if (value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
}
