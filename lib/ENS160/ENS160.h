#ifndef ENS160_H
#define ENS160_H

#include <Wire.h>
#include "structs.h"

class ENS160 {
	public:
		ENS160(const char * name);
		~ENS160();
		int get_eco2();
		int get_tvoc();
		int get_air_quality();
		void set_temp(float temp);
		void set_humid(float humid);
		void get_mode();
		void deep_sleep();
		void sleep();
		void wake();
        void read();
        Sensor * get_data();
	private:
        Sensor * sensor;
		uint8_t state;
		uint16_t eco2;
		uint16_t tvoc;
		uint8_t air_quality;
};

#endif