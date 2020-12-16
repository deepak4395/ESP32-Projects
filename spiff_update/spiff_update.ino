// ADD bin file to sketchfolder/data and upload to esp32 spiff using tools/esp32 sketch data upload.
#include <Update.h>
#include <FS.h>
#include "SPIFFS.h"

// perform the actual update from a given stream
void performUpdate(Stream &updateSource, size_t updateSize) {
  if (Update.begin(updateSize)) {
    size_t written = Update.writeStream(updateSource);
    if (written == updateSize) {
      Serial.println("Written : " + String(written) + " successfully");
    }
    else {
      Serial.println("Written only : " + String(written) + "/" + String(updateSize) + ". Retry?");
    }
    if (Update.end()) {
      Serial.println("OTA done!");
      if (Update.isFinished()) {
        Serial.println("Update successfully completed. Rebooting.");
      }
      else {
        Serial.println("Update not finished? Something went wrong!");
      }
    }
    else {
      Serial.println("Error Occurred. Error #: " + String(Update.getError()));
    }

  }
  else
  {
    Serial.println("Not enough space to begin OTA");
  }
}

// check given FS for valid update.bin and perform update if available
void updateFromFS(fs::FS &fs) {
  File updateBin = fs.open("/update.bin");
  if (updateBin) {
    if (updateBin.isDirectory()) {
      Serial.println("Error, update.bin is not a file");
      updateBin.close();
      return;
    }

    size_t updateSize = updateBin.size();

    if (updateSize > 0) {
      Serial.println("Try to start update");
      performUpdate(updateBin, updateSize);
    }
    else {
      Serial.println("Error, file is empty");
    }

    updateBin.close();

    // whe finished remove the binary from sd card to indicate end of the process
    fs.remove("/update.bin");
  }
  else {
    Serial.println("Could not load update.bin from sd root");
  }
}

void setup() {
  uint8_t cardType;
  Serial.begin(115200);
  Serial.println("Welcome to the SD-Update example!");

  // You can uncomment this and build again
  // Serial.println("Update successfull");

  //first init and check SD card
  if (!SPIFFS.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  else {
    Serial.println("Card Mount done");
    updateFromFS(SPIFFS);
  }
}

void rebootEspWithReason(String reason) {
  Serial.println(reason);
  delay(1000);
  ESP.restart();
}

//will not be reached
void loop() {

}
