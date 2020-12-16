
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
volatile int16_t encoder0Pos = 0;
uint8_t old_AB = 0;
int16_t steps = 0;
bool reFlag = false;
uint8_t encoderAPin = 21;
uint8_t encoderBPin = 22;
uint8_t encoderButtonPin = 23;
uint8_t encoderSteps = 2;
int16_t lastReadEncoder0Pos = 0;
int8_t enc_states[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

void IRAM_ATTR readEncoder_ISR()
{
  portENTER_CRITICAL_ISR(&(mux));
  old_AB <<= 2;                   //remember previous state
  int8_t ENC_PORT = ((digitalRead(encoderBPin)) ? (1 << 1) : 0) | ((digitalRead(encoderAPin)) ? (1 << 0) : 0);
  old_AB |= ( ENC_PORT & 0x03 );  //add current state
  encoder0Pos += ( enc_states[( old_AB & 0x0f )]);
  int16_t _encoder0Pos = encoder0Pos / encoderSteps;
  int16_t encoder0Diff = _encoder0Pos - lastReadEncoder0Pos;
  lastReadEncoder0Pos = _encoder0Pos;
  if (encoder0Diff != 0) {
    encoder += encoder0Diff;
    reFlag = true;
  }
  if (encoder > 40)encoder = 40;
  if (encoder < 0)encoder = 0;
  steps = map(encoder, 0, 40, 0, 100);
  portEXIT_CRITICAL_ISR(&(mux));
}

void reSetup() {
  pinMode(encoderAPin, INPUT);
  pinMode(encoderBPin, INPUT);
  pinMode(encoderButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderAPin), readEncoder_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderBPin), readEncoder_ISR, CHANGE);
}

void reLoop() {
  if (reFlag) {
    Power = steps;
    dimmerSetPower(Power); // 0 - 97 not 0 to 100 flicker at 98 to 100
    Dev5->setPercent(Power);
    reFlag = false;
  }
}
