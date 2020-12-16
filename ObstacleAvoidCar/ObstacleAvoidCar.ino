#include <NewPing.h>
int motorPin[] = {33, 25, 26, 27}; //left - right
int connectionLed = 2;
String carMovement = "default", carMovementP;
int carSpeed = 130;
#define TRIGGER_PIN  18
#define ECHO_PIN     19
#define MAX_DISTANCE 200
#define Debug
#ifdef Debug
#define D(x) Serial.print(x)
#define Dln(x) Serial.println(x)
#else
#define D(x)
#define Dln(x)
#endif
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
void fullstop() {
  for (int i = 0; i < 4; i++) {
    ledcWrite(i, 0);
  }
}
void backward(int i) {
  fullstop();
  delay(100);
  ledcWrite(0, 0);
  ledcWrite(1, i);
  ledcWrite(2, i);
  ledcWrite(3, 0);
}
void forward(int i) {
  fullstop();
  delay(100);
  ledcWrite(0, i);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, i);
}

void right(int i) {
  fullstop();
  delay(100);
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, i);
}

void left(int i) {
  fullstop();
  delay(100);
  ledcWrite(0, i);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}

void updateCar() {
  D("Making car ");
  if (carMovement == "forward") {
    D("move Forward with speed ");
    Dln(carSpeed);
    forward(carSpeed);
  }
  else if (carMovement == "backward") {
    D("move Backward with speed ");
    Dln(carSpeed);
    backward(carSpeed);
  }
  else if (carMovement == "left") {
    D("move Left with speed ");
    Dln(carSpeed);
    left(carSpeed);
  }
  else if (carMovement == "right") {
    D("move Right with speed ");
    Dln(carSpeed);
    right(carSpeed);
  }
  else if (carMovement == "stop") {
    Dln("Fullstop");
    fullstop();
  }
}

void testCar() {
  Dln("Testing Car Movement");
  while (1) {
    forward(carSpeed);
    delay(2000);
    backward(carSpeed);
    delay(2000);
    left(carSpeed);
    delay(2000);
    right(carSpeed);
    delay(2000);
    fullstop();
    delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  Dln("Setup Started");
  Serial.println("Pin Setup");
  for (int i = 0; i < 4; i++) {
    ledcSetup(i, 5000, 8);
    ledcAttachPin(motorPin[i], i);
  }
  pinMode(connectionLed, OUTPUT);
  digitalWrite(connectionLed, LOW);
  //testCar();
  Dln("Setup Ended");
}

void loop() {
  delay(50);
  int i = sonar.ping_cm();
  Serial.print("Ping: ");
  Serial.print(i); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  if (i < 30 && i > 0) {
    carMovement = "right";
  }
  else carMovement = "forward";
  if (carMovement != carMovementP) {
    carMovementP = carMovement;
    updateCar();
    delay(2000); // to let the movement complete
  }
}
