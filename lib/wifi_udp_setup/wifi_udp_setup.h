#ifndef wifi_udp_setup_h
#define wifi_udp_setup_h

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

extern const char* ssid;
extern const char* password;
extern const char* udp_server;
extern const int udp_port;
extern String macAddress;
extern WiFiUDP udp;

void setupWiFiUDP();

#endif
