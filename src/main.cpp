#include "main.h"

AHT20 aht20("room monitor");
ENS160 ens160("gas sensor");

void setup() {
    Wire.begin();
    Serial.begin(9600);
    delay(500);
    // setupWiFiUDP();
    ens160.wake();
}


void loop() {
    JsonDocument doc;
    unsigned long start_time = millis();



    aht20.read();

    Serial.print("Temperature: ");
    Serial.print(aht20.get_temperature());
    Serial.println("°C");
    
    Serial.print("Humidity: ");
    Serial.print(aht20.get_humidity());
    Serial.println("%");

    // ens160.set_temp(aht20.get_temperature());
    // ens160.set_humid(aht20.get_humidity());

    Serial.print("eCO2: ");
    Serial.print(ens160.get_eco2());
    Serial.println(" ppm");
    Serial.print("TVOC: ");
    Serial.print(ens160.get_tvoc());
    Serial.println(" ppb");
    Serial.print("Air Quality: ");
    Serial.println(ens160.get_air_quality());

    Serial.println();

    delay(1000);


    while (false) {

        // Send artificial sensor data
        doc.clear();
        doc["message_type"] = "sensor_data";
        doc["mac"] = macAddress;
        doc["sensors"]["bonsai"]["moisture"] = random(0, 100);
        doc["sensors"]["room monitor"]["temperature"] = random(-100, 0);
        doc["sensors"]["room monitor"]["humidity"] = random(0, 200);
        doc["run_time"] = millis() - start_time;

        char buffer[255];
        serializeJson(doc, buffer);

        udp.beginPacket(udp_server, udp_port);
        udp.write(buffer);
        udp.endPacket();

        Process_response();

        delay(5000);

    }
}


    
