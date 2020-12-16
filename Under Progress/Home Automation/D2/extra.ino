/*
    digitalWrite(R[i], V[i]);
*/

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
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
