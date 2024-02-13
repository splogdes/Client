#ifndef server_response_h
#define server_response_h

#include <ArduinoJson.h>
#include "wifi_udp_setup.h"

extern String macAddress;
extern WiFiUDP udp;

void Process_response();
void registerDevice();
void registerSensor(const char *sensorName , const char *sensorModel);

#endif
