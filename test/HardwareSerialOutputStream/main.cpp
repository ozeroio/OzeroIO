#include <Arduino.h>
#include <HardwareSerialOutputStream/HardwareSerialOutputStream.cpp>
#include <OutputStream/OutputStream.cpp>

#include "../test.cpp"

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 1000
#else
#define LEN 256
#endif

void setup() {
	Serial.begin(115200);

	log("Initializing...");

	HardwareSerialOutputStream os;

	assertTrueThat("Mark is not supported", !os.markSupported());
	const char *str = "Writing: << PASSED ";
	os.write((unsigned char *) str, 0, 19);
	os.write('>');
	os.write('>');
	os.write('\n');
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}