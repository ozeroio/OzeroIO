#include <Arduino.h>
#include <HardwareSerialInputStream/HardwareSerialInputStream.cpp>
#include <InputStream/InputStream.cpp>
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

	HardwareSerialInputStream is(&Serial);
	HardwareSerialOutputStream os(&Serial);

	assertTrueThat("Mark is not supported", !is.markSupported());
	log("Echoing from now on...");
	for (;;) {
		if (is.available() > 0) {
			os.write(is.read());
			os.write(',');
		}
	}
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}