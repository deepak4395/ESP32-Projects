int zero = 0;
int voltPin = A6;
void vsSetup() {
  pinMode(A6, INPUT);
  Calibrate();
}
void Calibrate() {
  Serial.println("Vs calibration Started");
  Serial.println("Light Off");
  long acc = 0;
  for (int i = 0; i < 100; i++) {
    acc = acc + analogRead(A6);
    delay(10);
  }
  zero = acc / 100;
  Serial.println("Done");
}

int voltage() {
  int maxValue = 0;
  int x = 0;
  for (int i = 0; i < 100; i++) {
    x = abs(zero - analogRead(A6));
    if (x > maxValue) maxValue = x;
    delay(10);
  }
  if (maxValue < 50) maxValue = 0;
  return maxValue;
}
