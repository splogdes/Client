#include "main.h"

void setup() {
  Serial.begin(9600);
  setupWiFiUDP();
}

void loop() {
  JsonDocument doc;
  int counter = 0;

  while (true) {
    counter++;

    if (counter % 2 == 0) {
      doc["type"] = "soil_data";
      doc["mac"] = macAddress;
      doc["soil_moisture"] = random(0, 100);
    } else {
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
        registerDevice();
      }
    }
    delay(5000);
  }
}
