#include "server_response.h"


void registerDevice() {
    JsonDocument doc;

    doc["message_type"] = "register_device";
    doc["mac"] = macAddress;
    doc["model"] = "D1-mini";
    doc["location"] = "table";

    char buffer[255];
    serializeJson(doc, buffer);

    udp.beginPacket(udp_server, udp_port);
    udp.write(buffer);
    udp.endPacket();
}

void registerSensor(const char *sensorName, const char *sensorModel) {
    JsonDocument doc;

    doc["message_type"] = "register_sensor";
    doc["mac"] = macAddress;
    doc["name"] = sensorName;
    doc["model"] = sensorModel;

    char buffer[255];
    serializeJson(doc, buffer);

    udp.beginPacket(udp_server, udp_port);
    udp.write(buffer);
    udp.endPacket();
}

void Process_response() {

    int packetSize = udp.parsePacket();

    if (packetSize) {

        char packetBuffer[255];
        int len = udp.read(packetBuffer, 255);

        if (len > 0) {
        packetBuffer[len] = 0;
        }

        Serial.print("Received response from server: ");
        Serial.println(packetBuffer);

        if (strcmp(packetBuffer, "register_device") == 0) {
        registerDevice();

        }else if (strcmp(packetBuffer, "room monitor") == 0) {
        registerSensor("room monitor", "AHT21");

        }else if (strcmp(packetBuffer, "bonsai") == 0) {
        registerSensor("bonsai", "capacitive");

        }

    }
}