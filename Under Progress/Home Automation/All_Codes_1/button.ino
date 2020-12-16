const int F[noOfSwitch] = {4, 16, 17, 5};

int Time[noOfSwitch] = {millis(), millis(), millis(), millis()};
int x[noOfSwitch], px[noOfSwitch] = {1, 1, 1, 1};
void buttonSetup() {
  for (int i = 0; i < noOfSwitch; i++) {
    pinMode(F[i], INPUT_PULLUP);
  }
}
void buttonUpdate() {
  for (int i = 0; i < noOfSwitch; i++) {
    x[i] = digitalRead(F[i]);
    if (!x[i]) {
      px[i] = x[i];
      Time[i] = millis();
    }
    if (!px[i] && x[i] && millis() - Time[i] > 25) {
      px[i] = x[i];
      V[i] = !V[i];
      buttonFlag = true;
    }
  }
}
