#include "wifi_udp_setup.h"

const char* ssid = "Oliver’s iPhone";
const char* password = "123456789";
const char* udp_server = "172.20.10.3";
const int udp_port = 5005;
String macAddress = WiFi.macAddress();
WiFiUDP udp;

void setupWiFiUDP() {

	Serial.println("");
	Serial.print("Connecting to WiFi");
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
	}

	Serial.println("Connected to WiFi");

	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	Serial.print("MAC address: ");
	Serial.println(macAddress);

	udp.begin(udp_port);
}
