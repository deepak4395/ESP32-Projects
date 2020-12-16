#include <ESP32Ping.h>
const char* remote_host = "www.google.com";
bool pingRemote(){
  Dln("Pinging...");
  if(Ping.ping(remote_host)) {
    Dln("Ping Successful");
    return true;
  }
  else {
    Dln("Ping Unsuccessful");
    return false;
  }
}
