int Time[noOfSwitch], TimeUp = millis(), TimeDown = millis();
int x[noOfSwitch], px[noOfSwitch], Up, Down, pUp, pDown;

void buttonSetup() {
  for (int i = 0; i < noOfSwitch; i++) {
    pinMode(F[i], INPUT_PULLUP);
  }
  pinMode(DimmerUp, INPUT_PULLUP);
  pinMode(DimmerDown, INPUT_PULLUP);
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
  Up = digitalRead(DimmerUp);
  if (!Up) {
    pUp = Up;
    TimeUp = millis();
  }
  if (!pUp && Up && millis() - TimeUp > 25) {
    pUp = Up;
    Power = Power + 10;
    if (Power > 100) Power = 100;
    powerFlag = true;
  }

  Down = digitalRead(DimmerDown);
  if (!Down) {
    pDown = Down;
    TimeDown = millis();
  }
  if (!pDown && Down && millis() - TimeDown > 25) {
    pDown = Down;
    Power = Power - 10;
    if (Power < 0) Power = 0;
    powerFlag = true;
  }
}
