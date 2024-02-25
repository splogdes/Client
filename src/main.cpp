#include "main.h"

AHT20 aht20("room monitor");
ENS160 ens160("gas sensor");
UDP_Server udp_server("172.20.10.3", 5005);
Device device;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    delay(500);
    
    ens160.wake();
    
    udp_server.connect("Oliver’s iPhone", "123456789");
    udp_server.begin();

    device.model = "d1-mini";
    device.location = "room";
    device.sensors_size = 2;
    device.sensors = new Sensor * [2];
    device.sensors[0] = aht20.get_data();
    device.sensors[1] = ens160.get_data();
}


void loop() {
    aht20.read();
    ens160.read();
    udp_server.send_data(device);
    udp_server.process_response(device);
    delay(5000);
}


    
