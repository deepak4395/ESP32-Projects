#include <Preferences.h>
Preferences preferences[3];
void nvsSetup(){
  preferences[0].begin("Wifi Networks", false);
}
void loadCredentials() {
  preferences[0].getString("ssid", ssid, sizeof(ssid));
  preferences[0].getString("password", password, sizeof(password));
}

/** Store WLAN credentials to Preference */
void saveCredentials() {
  preferences[0].putString("ssid", ssid);
  preferences[0].putString("password", password);
}
void saveReboot(){
  preferences[0].putBool("Status",Reboot);
}
void loadReboot(){
  Reboot = preferences[0].getBool("Status",false);
}
