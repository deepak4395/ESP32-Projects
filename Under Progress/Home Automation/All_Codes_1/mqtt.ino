#include <PubSubClient.h>
WiFiClient wifiClient;
PubSubClient client(wifiClient);

const char* mqtt_server = "tailor.cloudmqtt.com";
#define mqtt_port 15699
#define MQTT_USER "cdwmpojq"
#define MQTT_PASSWORD "xGXr9zM6Rahq"

void callback(char* topic, byte *payload, unsigned int length) {
  D("New message from broker-");
  D("Channel:");
  String topic1 = String(topic);
  Dln(topic1);
  String Device = topic1.substring(topic1.indexOf("rd/") + 3);
  String D = "Light5";
  if (Device == D) {
    Power = atoi((char *)payload);
    powerFlag = true;
  }
  else {
    for (int i = 0; i < noOfSwitch; i++) {
      if (Name[i] == Device) {
        buttonFlag = true;
        if (!strncmp((char *)payload, "on", length)) {
          V[i] = 0;
        } else if (!strncmp((char *)payload, "off", length)) {
          V[i] = 1;
        }
      }
    }
  }
  Serial.println();
}


void reconnect() {
  bool state = true;
  int i = 0;
  Dln("Attempting MQTT connection");
  // Create a random client ID
  String clientId = "ESP32Client-";
  clientId += String(random(0xffff), HEX);
  while (!client.connected()) {
    // Attempt to connect
    client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD);
    delay(500);
    D(".");
    if (i > 10) {
      state = false; break;
    }
    i++;
  }
  if (state) {
    Dln("connected");
    client.subscribe("Name1/inward/#");
  }
  else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
  }
}

void mqttPublish(char *serialData) {
  if (!client.connected()) {
    reconnect();
  }
  client.publish("#", serialData);
}
void publishDevices(int i) {
  char *t, *p;
  String topic = "Name1/outward/" + Name[i];
  t = const_cast<char*>(topic.c_str());
  if (V[i]) p = "off";
  else p = "on";
  client.publish(t, p);
}

void publishPower() {
  char *t, *p = (char *)(&Power);
  String topic = "Name1/outward/Light5";
  t = const_cast<char*>(topic.c_str());
  //sprintf(p, "%d", Power);
  client.publish(t, p);
}
void mqttSetup() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}

void mqttLoop() {
  client.loop();
}
