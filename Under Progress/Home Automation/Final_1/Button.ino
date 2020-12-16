const int F1 = 4;
const int F2 = 16;
const int F3 = 17;
const int F4 = 5;


int Time1 = millis(), Time2 = millis(), Time3 = millis(), Time4 = millis();
int x, y, z, a, px = 1, py = 1, pz = 1, pa = 1;
void buttonSetup(){
  pinMode(F1, INPUT_PULLUP);
  pinMode(F2, INPUT_PULLUP);
  pinMode(F3, INPUT_PULLUP);
  pinMode(F4, INPUT_PULLUP);
}
void buttonUpdate() {
  x = digitalRead(F1);
  y = digitalRead(F2);
  z = digitalRead(F3);
  a = digitalRead(F4);

  if (!x) {
    px = x;
    Time1 = millis();
  }
  if (!px && x && millis() - Time1 > 25) {
    px = x;
    V1 = !V1;
    if (V1) Dev1->setValue(0); else Dev1->setValue(255);
    digitalWrite(R1, V1);
  }
  if (!y) {
    py = y;
    Time2 = millis();
  }
  if (!py && y && millis() - Time2 > 25) {
    py = y;
    V2 = !V2;
    if (V2) Dev2->setValue(0); else Dev2->setValue(255);
    digitalWrite(R2, V2);
  }
  if (!z) {
    pz = z;
    Time3 = millis();
  }
  if (!pz && z && millis() - Time3 > 25) {
    pz = z;
    V3 = !V3;
    if (V3) Dev3->setValue(0); else Dev3->setValue(255);
    digitalWrite(R3, V3);
  }
  if (!a) {
    pa = a;
    Time4 = millis();
  }
  if (!pa && a && millis() - Time4 > 25) {
    pa = a;
    V4 = !V4;
    if (V4) Dev4->setValue(0); else Dev4->setValue(255);
    digitalWrite(R4, V4);
  }

}
