#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PubSubClient.h>

#define wifi_ssid "YOUR-WiFI-SSID"
#define wifi_password "YOUR-WIFI-PASS"

#define mqtt_server "YOUR-MQTT-BROKER-ADDRESS"
#define mqtt_user "YOUR-MQTT-USER"
#define mqtt_password "YOUR-MQTT-PASS"

#define temperature_topic "sensor/temperature"

OneWire oneWire(2);
DallasTemperature ds(&oneWire);
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

bool checkBound(float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}

long lastMsg = 0;
float temp = 0.0;
float hum = 0.0;
float diff = 1.0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    
    ds.requestTemperatures();
    float newTemp = ds.getTempCByIndex(0);

    if (checkBound(newTemp, temp, diff)) {
      temp = newTemp;
      Serial.print("New temperature:");
      Serial.println(String(temp).c_str());
      client.publish(temperature_topic, String(temp).c_str(), true);
    }
  }

}
