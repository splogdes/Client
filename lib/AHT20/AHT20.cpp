#include "AHT20.h"


AHT20::AHT20(const char * name) {
    data = new uint8_t[7];
    state = 0;
    checksum = 0;
    sensor = new Sensor;
    sensor->name = name;
    sensor->model = "AHT20";
    sensor->data = new Sensor_data[2];
    sensor->data_size = 2;
    sensor->data[0].type = "temperature";
    sensor->data[0].unit = "C";
    sensor->data[1].type = "humidity";
    sensor->data[1].unit = "%";
}

AHT20::~AHT20() {
    delete[] sensor->name;
    for (int i = 0; i < sensor->data_size; i++) {
        delete[] sensor->data[i].type;
    }
    delete[] data;
    delete[] sensor->data;
    delete sensor;
}

float AHT20::get_temperature() {
    return sensor->data[0].value;
}

float AHT20::get_humidity() {
    return sensor->data[1].value;
}

bool AHT20::get_status() {
    return state;
}

bool AHT20::is_valid() {
    return checksum == crc8();
}

uint8_t AHT20::crc8() {
    const uint8_t polynomial = 0x31;
    uint8_t crc = 0xFF;

    for (size_t i = 0; i < 6; ++i) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; ++j) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

Sensor * AHT20::get_data() {
    return sensor;
}

void AHT20::read() {
    Wire.beginTransmission(0x38);
    Wire.write(0xAC);
    Wire.write(0x33);
    Wire.write(0x00);
    Wire.endTransmission();

    delay(100);

    Wire.requestFrom(0x38, 7);

    delay(100);

    uint8_t * data = new uint8_t[7];
    for (int i = 0; i < 7; i++) {
        data[i] = Wire.read();
    }

    state = data[0];

    int temp = ((data[3] & 0x0F) << 16) | (data[4] << 8) | data[5];
    sensor->data[0].value  = (float)temp / 1048576 * 200 - 50;

    int hum = (data[1] << 12) | (data[2] << 4) | (data[3] >> 4);
    sensor->data[1].value = (float)hum / 1048576 * 100;

    checksum = data[6];
}
