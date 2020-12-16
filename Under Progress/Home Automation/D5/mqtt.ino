#include <PubSubClient.h>
WiFiClient wifiClient;
PubSubClient client(wifiClient);

const char* mqtt_server = "tailor.cloudmqtt.com";
#define mqtt_port 15699
#define MQTT_USER "cdwmpojq"
#define MQTT_PASSWORD "xGXr9zM6Rahq"

#define MQTT_SERIAL_PUBLISH_CH "/icircuit/ESP32/serialdata/tx"
#define MQTT_SERIAL_RECEIVER_CH "/icircuit/ESP32/serialdata/rx"

void callback(char* topic, byte *payload, unsigned int length) {
  Serial.println("-------new message from broker-----");
  Serial.print("channel:");
  String topic1 = String(topic);
  String Device = topic1.substring(topic1.indexOf("rd/") + 3);
  Serial.println(Device);
  String D = "Light5";
  if (Device == D) {
    Power = atoi((char *)payload);
    powerFlag = true;
  }
  else {
    for (int i = 0; i < noOfSwitch; i++) {
      if (Name[i] == Device) {
        mqttFlag = true;
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
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
      //Once connected, publish an announcement...
      client.publish("Name1/outward", "hello world");
      client.publish("Name1/outward/D1", "hello world 2");
      // ... and resubscribe
      client.subscribe("Name1/inward/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqttPublish(char *serialData) {
  if (!client.connected()) {
    reconnect();
  }
  client.publish(MQTT_SERIAL_PUBLISH_CH, serialData);
}

void mqttSetup() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}

void mqttLoop() {
  client.loop();
}
