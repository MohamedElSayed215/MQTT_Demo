# MQTT Setup and Usage with Python

This repository provides a step-by-step guide to setting up MQTT and using Python scripts to publish and subscribe to MQTT messages.

---

## Prerequisites

1. **Python**: Ensure you have Python 3.6 or later installed.
2. **MQTT Broker**: Install an MQTT broker (e.g., Mosquitto).
3. **Paho MQTT Library**: Install the Python library to communicate with the MQTT broker.

---

## Installation

### Step 1: Install the MQTT Broker (Mosquitto)

#### For Ubuntu/Debian:
```bash
sudo apt update
sudo apt install mosquitto mosquitto-clients
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
