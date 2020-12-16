void restart() {
  ESP.restart();
  server.client().stop();
}

String SendHTML() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Drasti Smart Home</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Devices</h1>\n";
  ptr += "<p>";

  for (int i = 0; i < noOfSwitch; i++) {
    ptr += Name[i];
    if (!V[i]) {
      ptr += " Status: ON</p><a class=\"button button-off\" href=\"";
      ptr += "/devices/";
      ptr += i;
      ptr += "/value/1\">OFF</a>\n";
    }
    else {
      ptr += " Status: OFF</p><a class=\"button button-on\" href=\"";
      ptr += "/devices/";
      ptr += i;
      ptr += "/value/0\">ON</a>\n";
    }
  }
  ptr += "</p>";
  ptr += "<form action=\"devices/4/value/\" >";    // ?sCmd forced the '?' at the right spot
  ptr += "<BR>Light5 Power: &nbsp;&nbsp";  // perhaps we can show here the current value
  ptr += Power;   // this is just a scale depending on the max value; round for better readability
  ptr += " %";
  ptr += "<BR>";
  ptr += "<input style=\"width:200px; height:50px\" type=\"range\" name=\"ritika\" id=\"cmd\" value=\"";   // '=' in front of FUNCTION_200 forced the = at the right spot
  ptr += Power;
  ptr += "\" min=0 max=100 step=10 onchange=\"showValue(points)\" />"; //http://esp32.local/d?%3DFUNCTION_200=100
  ptr += "<BR><BR>";
  ptr += "<input type=\"submit\">";
  ptr += "</form>";
  ptr += "<p>";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void handleRoot() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", "");
  server.sendContent(
    "<html><head></head><body>"
    "<h1>Smart Home By Drasti</h1>"
  );
  if (server.client().localIP() == apIP) {
    server.sendContent(String("<p>You are connected through the soft AP: ") + softAP_ssid + "</p>");
    server.sendContent("<p><a href='/wifi'>Config the wifi connection</a> for alexa and remote acess features .</p>");
  } else {
    server.sendContent(String("<p>You are connected through the wifi network: ") + ssid + "</p>");
  }
  server.sendContent(
    "<p>You may want to <a href='/wifi'>config the wifi connection</a>.</p>"
    "<p>You may want to <a href='/restart'>Restart</a>.</p>"
    "</body></html>"
  );
  server.sendContent(SendHTML());
  server.client().stop();
}

void serverSetup() {
  server.on("/", handleRoot);
  server.on("/devices/{}/value/{}", []() {
    int device = server.pathArg(0).toInt();
    int value = server.pathArg(1).toInt();
    if (device < noOfSwitch) {
      if (value == 1)V[device] = true; else V[device] = false;
      buttonFlag = true;
    }
    else {
      Power = server.arg("ritika").toInt();
      powerFlag = true;
    }
    server.sendHeader("Location", "/");
    server.send(303);
    server.client().stop();
  });
  server.on("/restart", restart);
  server.onNotFound([]() {
    if (!espalexa.handleAlexaApiCall(server.uri(), server.arg(0)))
    {
      server.send(404, "text/plain", "Not found");
    }
  });
}
