#ifndef AHT20_H
#define AHT20_H

#include <Wire.h>
#include "structs.h"

class AHT20 {
	public:
		AHT20(const char * name);
		~AHT20();
		void read();
		float get_temperature();
		float get_humidity();
		bool get_status();
		bool is_valid();
        Sensor * get_data();
	private:
		uint8_t crc8();
		uint8_t state;
		uint8_t checksum;
		uint8_t * data;
        const char * name;
        Sensor * sensor;
};


#endif