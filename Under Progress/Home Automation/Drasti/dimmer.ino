#include <RBDdimmer.h>

#define outputPin  32
#define zerocross  33

dimmerLamp dimmer(outputPin, zerocross);

void dimmerSetup(){
  dimmer.begin(NORMAL_MODE, ON);
}
void dimmerSetPower(int i){
  dimmer.setPower(i);
}
