#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// MQTT credentials
const char* mqtt_server = "46ecfaf93a7b4d4b87b953f6cdc35b6d.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "ADAS_GP_25";
const char* mqtt_password = "ADAS_Gp_25";
const char* mqtt_topic = "GP/ADAS";

// Create WiFiClientSecure and PubSubClient
WiFiClientSecure secureClient;
PubSubClient client(secureClient);

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
  // Set insecure if you don't verify certificate (not recommended for production)
  secureClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);

  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("✅ Connected to MQTT broker.");
    } else {
      Serial.print("❌ Failed. Code = ");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
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

  client.loop();

  // Replace this with actual data or sensor input
  String message = "Test from ESP32";
  client.publish(mqtt_topic, message.c_str());
  Serial.println("📤 Message sent: " + message);

  delay(5000);  // Wait 5 seconds between messages
}
