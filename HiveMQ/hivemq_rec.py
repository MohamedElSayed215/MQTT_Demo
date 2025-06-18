import paho.mqtt.client as mqtt
import ssl

# إعدادات HiveMQ Cloud
BROKER = "46ecfaf93a7b4d4b87b953f6cdc35b6d.s1.eu.hivemq.cloud"
PORT = 8883
USERNAME = "ADAS_GP_25"
PASSWORD = "ADAS_Gp_25"
TOPIC = "GP/ADAS"

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("✅ Connected successfully to broker.")
        client.subscribe(TOPIC)
        print(f"📡 Subscribed to topic: {TOPIC}")
    else:
        print(f"❌ Connection failed with code {rc}")


def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print(f"📥 Message received on '{msg.topic}': {message}")


client = mqtt.Client()
client.username_pw_set(USERNAME, PASSWORD)
client.tls_set(tls_version=ssl.PROTOCOL_TLS)


client.on_connect = on_connect
client.on_message = on_message


client.connect(BROKER, PORT, 60)

print("🚀 Waiting for messages... Press Ctrl+C to exit.\n")
client.loop_forever()
