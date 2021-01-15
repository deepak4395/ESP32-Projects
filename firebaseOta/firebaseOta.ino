#define FIREBASE_HOST "calibrex-5b953-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "uTFvzDHJYSrO0f6FvTVOOdOadvpIwnxBap40ruWH"
#define WIFI_SSID "M 57"
#define WIFI_PASSWORD "8376918157"
long UPDATE_CHECK_TIME = 5000;

String ver = "1.0.0.1";

#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <FirebaseESP32.h>

FirebaseData firebaseData;
const char rootCACertificate[] PROGMEM = "-----BEGIN CERTIFICATE-----\n"
    "MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n"
    "A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n"
    "Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n"
    "MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n"
    "A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n"
    "hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n"
    "v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n"
    "eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n"
    "tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n"
    "C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n"
    "zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n"
    "mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n"
    "V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n"
    "bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n"
    "3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n"
    "J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n"
    "291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n"
    "ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n"
    "AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n"
    "TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n"
    "-----END CERTIFICATE-----\n";

void setup() {
  Serial.begin(115200);
  Serial.print("Running Firmware Ver: ");
  Serial.println(ver);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, rootCACertificate);
}

void loop() {
  checkUpdate();
}
long lastUpdateCheck = millis();
void checkUpdate() {
  if (millis() - lastUpdateCheck > UPDATE_CHECK_TIME) {
    lastUpdateCheck = millis();
    if (Firebase.getBool(firebaseData, "/firmware/updateAvailable"))
    {
      bool b = firebaseData.boolData();
      if (b) {
        Serial.println("Update Available");
        if (!Firebase.setBool(firebaseData, "/firmware/updateAvailable", false))
        {
          Serial.print("Error in setBool /firmware/updateAvailable, ");
          Serial.println(firebaseData.errorReason());
        }
        if (Firebase.getString(firebaseData, "/firmware/URL")) {
          String s = firebaseData.stringData();
          Serial.println("Firmare URL=");
          Serial.println(s);
          updateFirmware(s);
        }
        else {
          Serial.print("Error in getString /firmware/URL, ");
          Serial.println(firebaseData.errorReason());
        }
      }
      else Serial.println("No Updates");
    } else {
      Serial.print("Error in getBool /firmware/updateAvailable, ");
      Serial.println(firebaseData.errorReason());
    }
  }
}
void updateFirmware(String url) {
  WiFiClientSecure client;
  client.setCACert(rootCACertificate);
  client.setTimeout(12000 / 1000); // timeout argument is defined in seconds for setTimeout
  httpUpdate.setLedPin(2, HIGH);
  Serial.println("Uploading..");
  t_httpUpdate_return ret = httpUpdate.update(client, url);
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("HTTP_UPDATE_NO_UPDATES");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("HTTP_UPDATE_OK");
      break;
  }
}
