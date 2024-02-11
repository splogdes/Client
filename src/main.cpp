#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>


const char* ssid = "Oliver’s iPhone";
const char* password = "123456789";

const char* udp_server = "172.20.10.3";
const int udp_port = 5005;

String macAddress = WiFi.macAddress();  

WiFiUDP udp;


void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("");
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  

  Serial.println("Connected to WiFi");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC address: ");
  Serial.println(macAddress);

  udp.begin(udp_port);

}

void register_device() {
  StaticJsonDocument<200> doc;

  doc["type"] = "register_device";
  doc["mac"] = macAddress;
  JsonObject sensors = doc.createNestedObject("sensors");
  sensors["temperature"] = "DHT11";
  sensors["humidity"] = "SHT30";
  doc["model"] = "D1-mini";
  doc["location"] = "table";

  char buffer[255];
  serializeJson(doc, buffer);

  udp.beginPacket(udp_server, udp_port);
  udp.write(buffer);
  udp.endPacket();
}

int counter = 0;

void loop() {

  StaticJsonDocument<200> doc;

  counter++;

  if (counter % 2 == 0){
    doc["type"] = "soil_data";
    doc["mac"] = macAddress;
    doc["soil_moisture"] = random(0, 100);
  }
  else{
    doc["type"] = "sensor_data";
    doc["mac"] = macAddress;
    doc["temperature"] = random(0, 100);
    doc["humidity"] = random(-100, 100);
  }

  char buffer[255];
  serializeJson(doc, buffer);

  udp.beginPacket(udp_server, udp_port);
  udp.write(buffer);
  udp.endPacket();

  delay(500);

  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received response from server: ");

    char packetBuffer[255];

    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println(packetBuffer);

    if (strcmp(packetBuffer, "register_device") == 0) {
      register_device();
    }

  }
  delay(5000);

}