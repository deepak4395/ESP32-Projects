#include "RTClib.h"
RTC_DS3231 rtc;
char buf1[] = "YYYY MMM DD DDD-hh:mm:ss";
char buf2[] = "hhmm";
int onTime = 1529, offTime = 1530;
void rtcSetup() {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}
String nowTime(int i) {
  DateTime now = rtc.now();
  if (i)return now.toString(buf1);
  else return now.toString(buf2);
}
float temperature() {
  return rtc.getTemperature();
}
bool night() {
  if (nowTime(0).toInt() > onTime && nowTime(0).toInt() < offTime){ return true;}
  else return false;
}
