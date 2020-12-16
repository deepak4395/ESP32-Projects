//#include <Preferences.h>
//Preferences p[2];
//
//void nvsSetup() {
//  p[0].begin("Wifi Networks", false);
//  p[1].begin("Load", false);
//  for (int i = 0; i < noOfSwitch; i++) {
//    V[i] = p[1].getBool(&R[i]);
//  }
//  Power = p[1].getInt(&outputPin, 50);
//}
////void loadCredentials() {
////  p[0].getString("ssid", ssid, sizeof(ssid));
////  p[0].getString("password", password, sizeof(password));
////}
////void saveCredentials() {
////  p[0].putString("ssid", ssid);
////  p[0].putString("password", password);
////}
//
////void updateLoad() {
////  for (int i = 0; i < noOfSwitch; i++) {
////    V[i] = p[1].getBool(Name[i], LOW);
////  }
////  Power = p[1].getInt(outputPin, 50);
////}
//
//void saveLoad(int i) {
//  if (i < noOfSwitch)p[1].putBool(&R[i], V[i]);
//  else p[1].putInt(&outputPin, Power);
//}
