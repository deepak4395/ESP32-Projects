int T = millis();
void loop() {
  //otaWebLoop();
  alexaLoop();
  buttonUpdate();
  reLoop();
  if (millis() - T > 1000) {
    T = millis();
    for (int i = 0; i < noOfSwitch; i++) {
    bool test = p[1].getBool(&R[i]);
    Serial.print(test);
  }
  int P = p[1].getInt(&outputPin, 50);
   Serial.println(P);
  }
}
