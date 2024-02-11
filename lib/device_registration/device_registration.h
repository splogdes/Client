#ifndef device_registration_h
#define device_registration_h

#include <ArduinoJson.h>
#include "wifi_udp_setup.h"

extern String macAddress;
extern WiFiUDP udp;

void registerDevice();

#endif
