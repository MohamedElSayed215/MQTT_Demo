#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// MQTT Broker info
const char* mqtt_server = "46ecfaf93a7b4d4b87b953f6cdc35b6d.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "ADAS_GP_25";
const char* mqtt_password = "ADAS_Gp_25";
const char* mqtt_topic = "GP/ADAS";

// TLS Client
WiFiClientSecure secureClient;
PubSubClient client(secureClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("📥 Message received on topic '");
  Serial.print(topic);
  Serial.print("': ");

  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected.");
}

void connectMQTT() {
  secureClient.setInsecure();  // Don't verify cert (for testing only)

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker...");

    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("✅ Connected to broker.");
      client.subscribe(mqtt_topic);
      Serial.print("📡 Subscribed to topic: ");
      Serial.println(mqtt_topic);
    } else {
      Serial.print("❌ Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  connectWiFi();
  connectMQTT();
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();  // Keep MQTT connection alive and receive messages
}
