void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }
  nowSetup();
  i2csetup();
}

void loop() {
  nowLoop();
  i2cloop();
  if (Az > 0.4) handPosition = "forward";
  else if (Az < -0.4) handPosition = "backward";
  else if (Ay < -0.4) handPosition = "right";
  else if (Ay > 0.3) handPosition = "left";
  else handPosition = "stop";
  if (handPosition != carMovementP) {
    Serial.println(handPosition);
    carMovementP = handPosition;
    carMovement = handPosition+String(";speed=") + String(carSpeed);
    string("U");
    WifiEspNow.send(serverAddress, reinterpret_cast<const uint8_t*>(uName), strlen(uName));
  }
}
