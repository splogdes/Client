#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    const char * type;
    float value;
} Sensor_data;

typedef struct {
    const char * name;
    const char * model;
    Sensor_data * data;
    int data_size;
} Sensor;

typedef struct {
    const char * model;
    const char * location;
    Sensor ** sensors;
    int sensors_size;
} Device;

#endif