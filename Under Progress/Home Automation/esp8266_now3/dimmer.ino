#include <RBDdimmer.h>

dimmerLamp dimmer(outputPin, zerocross);

void dimmerSetup() {
  dimmer.begin(NORMAL_MODE, ON);
}

void dimmerSetPower(int i) {
  dimmer.setPower(i);
}
