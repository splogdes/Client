#ifndef main_h
#define main_h

#include <ArduinoJson.h>
#include <Wire.h>
#include "structs.h"
#include "udp_server.h"
#include "AHT20.h"
#include "ENS160.h"


extern String macAddress;
extern WiFiUDP udp;

#endif
