/*

*/


bool pinZero = false;
int TimeZero = millis();
const int ResetTime = 5000;
const int resetPin = 0;
bool resetCheck() {
  if (digitalRead(R[resetPin])) {
  TimeZero = millis();
  }
  else {
    if (millis() - TimeZero > 5000) return true;
  }
  return false;
}

void reboot(){
  // clear nvs/eeprom
  WiFi.disconnect();
  apModeStart();
  serverSetup();
  
  
  
}
/** Is this an IP? */
boolean isIp(String str) {
  for (int i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) {
      return false;
    }
  }
  return true;
}

/** IP to String? */
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}
