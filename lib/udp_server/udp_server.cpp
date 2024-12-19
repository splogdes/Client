#include "udp_server.h"

UDP_Server::UDP_Server(String udp_server, const int udp_port) :
udp_server(udp_server),
udp_port(udp_port),
mac_address(WiFi.macAddress()) {
    Serial.print("MAC address: ");
    Serial.println(mac_address);
}

UDP_Server::~UDP_Server() {
}

void UDP_Server::connect(String ssid, String password) {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    ip = WiFi.localIP();
    Serial.println("\nConnected to WiFi");
}

void UDP_Server::begin() {
    udp.begin(udp_port);
    Serial.print("Listening on port: ");
    Serial.println(udp_port);
}

void UDP_Server::process_response(Device device) {
    int packetSize = udp.parsePacket();
    if (packetSize) {
        char packet_buffer[255];
        int len = udp.read(packet_buffer, 255);
        if (len > 0) {
            packet_buffer[len] = 0;
        }
        Serial.print("Received response from server: ");
        Serial.println(packet_buffer);
        if (strcmp(packet_buffer, "register_device") == 0) {
            register_device(device);
        } else {
            for (int i = 0; i < device.sensors_size; i++) {
                if (strcmp(packet_buffer, device.sensors[i]->name) == 0) {
                    register_sensor(*device.sensors[i]);
                }
            }
        }
    }
}

void UDP_Server::register_device(Device device) {
    JsonDocument doc;
    doc["message_type"] = "register_device";
    doc["mac"] = mac_address;
    doc["model"] = device.model;
    doc["location"] = device.location;
    send_json(doc);
}

void UDP_Server::register_sensor(Sensor sensor) {
    JsonDocument doc;
    doc["message_type"] = "register_sensor";
    doc["mac"] = mac_address;
    doc["name"] = sensor.name;
    doc["model"] = sensor.model;
    for (int i = 0; i < sensor.data_size; i++) {
        doc["modes"][sensor.data[i].type] = sensor.data[i].unit;
    }
    send_json(doc);
}

void UDP_Server::send_data(Device device) {
    JsonDocument doc;
    doc["message_type"] = "sensor_data";
    doc["mac"] = mac_address;
    for (int i = 0; i < device.sensors_size; i++) {
        Sensor * sensor = device.sensors[i];
        for (int j = 0; j < sensor->data_size; j++) {
            doc["sensors"][sensor->name][sensor->data[j].type] = sensor->data[j].value;
        }
    }
    send_json(doc);
}

void UDP_Server::send_json(JsonDocument doc) {
    char buffer[255];
    serializeJson(doc, buffer);
    udp.beginPacket(udp_server.c_str(), udp_port);
    udp.write(buffer);
    udp.endPacket();
}
