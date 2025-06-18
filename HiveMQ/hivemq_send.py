import paho.mqtt.client as mqtt
import ssl
import time


BROKER = "46ecfaf93a7b4d4b87b953f6cdc35b6d.s1.eu.hivemq.cloud"
PORT = 8883
USERNAME = "ADAS_GP_25"
PASSWORD = "ADAS_Gp_25"
TOPIC = "GP/ADAS"


client = mqtt.Client()
client.username_pw_set(USERNAME, PASSWORD)
client.tls_set(tls_version=ssl.PROTOCOL_TLS)

client.connect(BROKER, PORT, 60)
client.loop_start()

print("✅ Connected to MQTT Broker. Type 'exit' or 'q' to quit.\n")

try:
    while True:
        message = input("📝 Enter the data: ").strip()

        if message.lower() in ["exit", "q"]:
            print("👋 Exiting...")
            break

        if not message:
            print("⚠️ Please enter a non-empty message.")
            continue

        client.publish(TOPIC, message)
        print("📤 Message sent!")

        time.sleep(0.1)  
except KeyboardInterrupt:
    print("\n🔌 Interrupted. Disconnecting...")

client.loop_stop()
client.disconnect()
print("✅ Disconnected from broker.")
