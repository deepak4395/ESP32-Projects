int relayPin = 5;
int power = 0;
int p = 1000;
int volt;
double curr;

void setup () {
  Serial.begin(9600);
  rtcSetup();
  vsSetup();
  csSetup();
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}

void loop () {
  DateTime now = rtc.now();
  Serial.println(now.toString());

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
//  Serial.print(" (");
//  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  curr = current();
  volt = voltage();
  power = volt * curr;
  if (p != power) {
    p = power;
    Serial.println(nowTime(1));
    Serial.print(temperature());
    Serial.println(" °C");
    Serial.print(volt);
    Serial.println(" Vac");
    Serial.print(curr);
    Serial.println(" Amps RMS");
    Serial.print(power);
    Serial.println(" Watts");
    Serial.println();
  }
  //  Serial.println(nowTime(1));
  //  if (night()) {
  //    Serial.println("on");
  //    digitalWrite(relayPin, HIGH);
  //    nightFlag = false;
  //  }
  //  if (!night()) {
  //    Serial.println("off");
  //    digitalWrite(relayPin, LOW);
  //    nightFlag = true;
  //  }
}
