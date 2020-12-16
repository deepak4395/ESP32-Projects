#include <esp_now.h>
#include <WiFi.h>
uint8_t mac1[6]; //= (uint8_t *)malloc(sizeof(uint8_t)); // = {0x24, 0x0A, 0xC4, 0x31, 0xA7, 0x9C};
bool addFlag = false, flag2 = false;
int f = 0;
String deviceValue;
const uint16_t uChipId = ESP.getEfuseMac();
char *sC = "ServerCode";
void process(String s) {
  carMovement = s.substring(s.indexOf("Data-") + 5, s.indexOf(";s"));
  carSpeed = s.substring(s.indexOf("ed=") + 3, s.indexOf(";#")).toInt();
  D("Recived Car Movement ");
  D(carMovement);
  D(" with speed ");
  Dln(carSpeed);

  updateCar();
}
bool sendMesg(char *c) {
  D("Device ");
  esp_err_t result = esp_now_send(mac1, (uint8_t *)c, strlen(c));
  if (result == ESP_OK) {
    Dln(" Sent with success");
    return true;
  }
  else {
    if (result == ESP_ERR_ESPNOW_NOT_INIT) {
      Dln("ESPNOW not Init.");
    } else if (result == ESP_ERR_ESPNOW_ARG) {
      Dln("Invalid Argument");
    } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
      Dln("Internal Error");
    } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
      Dln("ESP_ERR_ESPNOW_NO_MEM");
    } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
      Dln("Peer not found.");
    } else {
      Dln("Not sure what happened");
    }
    return false;
  }
}
void onReceiveData(const uint8_t *mac, const uint8_t *data, int len) {

  D("Received from MAC: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", mac[i]);
    if (i < 5)D(":");
  }
  D(" ");
  String s;
  for (int i = 0; i < len; i++) s = s + (char)data[i];
  Dln(s);
  if (!memcmp(mac1, mac, 6)) {
    flag2 = true;
    if (s == "B- Hello Code") {
      sendMesg(sC);
    }
    if (s.charAt(0) == 'A' || s.charAt(0) == 'U') {
      process(s);
    }
  }
  else flag2 = false;

  if (s == "B- Hello Code" && !flag2) {
    memcpy(mac1, mac, 6);
    addFlag = true;
  }
}
