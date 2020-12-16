
const int csPin = A7;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module

void csSetup() {
  pinMode(csPin, INPUT);
}

double current()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  double Voltage = 0;
  double VRMS = 0;
  uint32_t start_time = millis();
  while ((millis() - start_time) < 1000) //sample for 1 Sec
  {
    readValue = analogRead(csPin);
    // see if you have a new maxValue
    if (readValue > maxValue)
    {
      /*record the maximum sensor value*/
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      /*record the minimum sensor value*/
      minValue = readValue;
    }
  }

  // Subtract min from max
  result = ((maxValue - minValue) * 5.0) / 1024.0;
  result = (result / 2.0) * 0.707; //root 2 is 0.707
  result = (result * 1000) / mVperAmp;
  if (result < 0.2) result = 0;
  return result ;
}
