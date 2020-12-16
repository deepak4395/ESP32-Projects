void setup() {
  // put your setup code here, to run once:
  pinMode(A6, INPUT);
  Serial.begin(9600);
  Calibrate();
}
int x = 0;
int zero = 0;

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(voltage());
  delay(100);
}

void Calibrate() {
  Serial.println("Calibration Started");
  Serial.println("Light Off");
  long acc = 0;
  for (int i = 0; i < 100; i++) {
    acc = acc + analogRead(A6);
    delay(10);
  }
  zero = acc / 100;
  Serial.println("Light On in 3 seconds");  
  Serial.println("  Done");
}

int voltage(){
  int maxValue=0;
  for (int i = 0; i < 100; i++) {
    x = abs(zero - analogRead(A6));
    if(x>maxValue) maxValue = x;
    delay(10);
  }
  return maxValue;
}
