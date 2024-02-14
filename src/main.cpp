#include "main.h"

void setup() {
	Serial.begin(9600);
	delay(100);
	setupWiFiUDP();
}

void loop() {
	JsonDocument doc;

	while (true) {

		// Send artificial sensor data
		doc.clear();
		doc["message_type"] = "sensor_data";
		doc["mac"] = macAddress;
		doc["sensors"]["bonsai"]["moisture"] = random(0, 100);
		doc["sensors"]["room monitor"]["temperature"] = random(-100, 0);
		doc["sensors"]["room monitor"]["humidity"] = random(0, 200);

		char buffer[255];
		serializeJson(doc, buffer);

		udp.beginPacket(udp_server, udp_port);
		udp.write(buffer);
		udp.endPacket();

		Process_response();

		delay(5000);

	}
}


	
