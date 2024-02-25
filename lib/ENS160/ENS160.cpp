#include "ENS160.h"

ENS160::ENS160(const char * name) {
    sensor = new Sensor;
    sensor->name = name;
    sensor->model = "ENS160";
    sensor->data = new Sensor_data[3];
    sensor->data_size = 3;
    sensor->data[0].type = "eco2";
    sensor->data[1].type = "tvoc";
    sensor->data[2].type = "air_quality";
}

ENS160::~ENS160() {
    delete[] sensor->name;
    for (int i = 0; i < sensor->data_size; i++) {
        delete[] sensor->data[i].type;
    }
    delete[] sensor->data;
    delete sensor;
}

int ENS160::get_eco2() {
    Wire.beginTransmission(0x52);
    Wire.write(0x24);
    Wire.endTransmission();
    Wire.requestFrom(0x52, 2);
    sensor->data[0].value = (float)(Wire.read() | (Wire.read() << 8));
    return sensor->data[0].value;
}

int ENS160::get_tvoc() {
    Wire.beginTransmission(0x52);
    Wire.write(0x22);
    Wire.endTransmission();
    Wire.requestFrom(0x52, 2);
    sensor->data[1].value = (float)( Wire.read() | (Wire.read() << 8));
    return sensor->data[1].value;
}

int ENS160::get_air_quality() {
    Wire.beginTransmission(0x52);
    Wire.write(0x21);
    Wire.endTransmission();
    Wire.requestFrom(0x52, 1);
    sensor->data[2].value = Wire.read();
    return sensor->data[2].value;
}

void ENS160::set_temp(float temp) {
    uint8_t tmp = (uint8_t) ((temp + 273.15f)*64.0f);
    Wire.beginTransmission(0x52);
    Wire.write(0x13);
    Wire.write(tmp & 0xFF);
    Wire.write(tmp >> 8);
    Wire.endTransmission();
}

void ENS160::set_humid(float humid) {
    uint8_t hum = (uint8_t) (humid*512.0f);
    Wire.beginTransmission(0x52);
    Wire.write(0x15);
    Wire.write(hum & 0xFF);
    Wire.write(hum >> 8);
    Wire.endTransmission();
}

void ENS160::get_mode() {
    Wire.beginTransmission(0x52);
    Wire.write(0x10);
    Wire.endTransmission();
    Wire.requestFrom(0x52, 1);
    state = Wire.read();
}

void ENS160::deep_sleep() {
    state = 0x00;
    Wire.beginTransmission(0x52);
    Wire.write(0x10);
    Wire.write(state);
    Wire.endTransmission();
}

void ENS160::sleep() {
    state = 0x01;
    Wire.beginTransmission(0x52);
    Wire.write(0x10);
    Wire.write(state);
    Wire.endTransmission();
}

void ENS160::wake() {
    if (state == 0x00){
        sleep();
        delay(100);
    }
    state = 0x02;
    Wire.beginTransmission(0x52);
    Wire.write(0x10);
    Wire.write(state);
    Wire.endTransmission();
}

Sensor * ENS160::get_data() {
    return sensor;
}

void ENS160::read() {
    get_eco2();
    get_tvoc();
    get_air_quality();
}