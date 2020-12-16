const int freq = 5000;
const int resolution = 8; //Resolution 8, 10, 12, 15

void pwmSetup(int Pin, int Channel){
  ledcSetup(Channel, freq, resolution);
  ledcAttachPin(Pin, Channel);
}
