#include <esp_now.h>
#include <WiFi.h>
const int noOfDevice = 20;
uint8_t mac1[noOfDevice][6]; //= (uint8_t *)malloc(sizeof(uint8_t)); // = {0x24, 0x0A, 0xC4, 0x31, 0xA7, 0x9C};
bool addFlag = false, flag2 = false;
int f = 0;
String deviceValue[noOfDevice];

const uint16_t uChipId = ESP.getEfuseMac();

char *sC="S***S";

void process(int i, String s) {
  deviceValue[i] = "Device-" + String(i+1) + ";" + s.substring(s.indexOf("Data-") + 5);
  Serial.println(deviceValue[i]);
}
bool sendMesg(int i,  char *c) {
  Serial.print("Device ");
  Serial.print(i+1);
  esp_err_t result = esp_now_send(mac1[i], (uint8_t *)c, strlen(c));
  if (result == ESP_OK) {
    Serial.println(" Sent with success");
    return true;
  }
  else {
    if (result == ESP_ERR_ESPNOW_NOT_INIT) {
      // How did we get so far!!
      Serial.println("ESPNOW not Init.");
    } else if (result == ESP_ERR_ESPNOW_ARG) {
      Serial.println("Invalid Argument");
    } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
      Serial.println("Internal Error");
    } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
      Serial.println("ESP_ERR_ESPNOW_NO_MEM");
    } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
      Serial.println("Peer not found.");
    } else {
      Serial.println("Not sure what happened");
    }
    return false;
  }
}
void onReceiveData(const uint8_t *mac, const uint8_t *data, int len) {
  Serial.print("Received from MAC: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", mac[i]);
    if (i < 5)Serial.print(":");
  }
  Serial.println();
  String s;
  for (int i = 0; i < len; i++) s = s + (char)data[i];
  Serial.println(s);

  for (int i = 0; i < f; i++) {
    if (!memcmp(mac1[i], mac, 6)) {
      flag2 = true;
      if (s == "B- Hello Code") {
        sendMesg(i, sC);
      }
      if (s.charAt(0) == 'A' || s.charAt(0) == 'U') {
        process(i, s);
      }
      break;
    }
    else flag2 = false;
  }
  if (s == "B- Hello Code" && !flag2) {
    memcpy(mac1[f], mac, 6);
    addFlag = true;
  }
}
