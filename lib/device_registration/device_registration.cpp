#include "device_registration.h"

void registerDevice() {
  JsonDocument doc;

  doc["type"] = "register_device";
  doc["mac"] = macAddress;
  JsonObject sensors = doc["sensors"].to<JsonObject>();
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
