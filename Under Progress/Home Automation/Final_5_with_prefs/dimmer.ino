#include <RBDdimmer.h>

const char outputPin = 32;
const char zerocross = 33;

dimmerLamp dimmer(outputPin, zerocross);

void dimmerSetup(){
  dimmer.begin(NORMAL_MODE, ON);
  dimmerSetPower(95);
}

void dimmerSetPower(int i){
  dimmer.setPower(i);
}
