# MQTT DS18B20 Temperature Sensor Software For ESP8266
Ready-To-Use Bulletproof DS18B20 MQTT Home Assistant-Compatable Software For ESP8266
## GPIO Pins
Connect Sensor To GPIO 2 (For NodeMCU/Wemos - D4)
## Libraries Used
- ESP8266WiFi.h
- OneWire.h
- DallasTemperature.h (3.8.0)
- PubSubCLient.h (Nick O'Leary, 2.8.0)
## Getting Started
1. Edit sone defines in config section: 
- wifi_ssid - Your Wi-Fi Network SSID
- wifi_password - Your Wi-Fi Network Password
- mqtt_server - IP Address/Domain Name of your MQTT Server
- mqtt_user - Your MQTT User 
- mqtt_password - Your MQTT Password
2. (Optional) Edit define "temperature_topic" that you wish
3. Flash the firmware to your ESP8266 board
4. Debug errors with built-in serial monitor
## Integrating Your Craft to Home Assistant
In this repository you can download a configuration.yaml template. Just copy and paste it in your configuration.yaml and you're ready to go!
