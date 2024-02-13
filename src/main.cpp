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


    // Send artificial sensor data
    doc.clear();
    doc["message_type"] = "sensor_data";
    doc["mac"] = macAddress;
    doc["sensors"]["bonsai"]["moisture"] = random(0, 100);
    doc["sensors"]["room monitor"]["temperature"] = random(-100, 0);
    doc["sensors"]["room monitor"]["humidity"] = random(0, 200);

    char buffer[255];
    serializeJson(doc, buffer);

    udp.beginPacket(udp_server, udp_port);
    udp.write(buffer);
    udp.endPacket();

    delay(500);

    Process_response();

    delay(5000);

  }
}


  
