#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include "structs.h"

class UDP_Server {
    public:
        UDP_Server(String udp_server, const int udp_port);
        ~UDP_Server();
        void connect(String ssid, String password);
        void begin();
        void process_response(Device device);
        void send_data(Device device);
    private:
        void register_sensor(Sensor sensor);
        void register_device(Device device);
        void send_json(JsonDocument doc);
        WiFiUDP udp;
        String udp_server;
        const int udp_port;
        IPAddress ip;
        const String mac_address;
};

#endif