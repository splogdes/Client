#ifndef main_h
#define main_h

#include <ArduinoJson.h>
#include "wifi_udp_setup.h"
#include "device_registration.h"

extern String macAddress;
extern WiFiUDP udp;

void mainLoop();

#endif
