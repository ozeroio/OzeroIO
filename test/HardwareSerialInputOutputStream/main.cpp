#include <Arduino.h>
#include <BufferedOutputStream/BufferedOutputStream.cpp>
#include <FilterOutputStream/FilterOutputStream.cpp>
#include <HardwareSerialInputStream/HardwareSerialInputStream.cpp>
#include <HardwareSerialOutputStream/HardwareSerialOutputStream.cpp>
#include <InputStream/InputStream.cpp>
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

	auto *streamBuffer = new uint8_t[16];

	HardwareSerialInputStream is;
	HardwareSerialOutputStream os;
	BufferedOutputStream bos(&os, streamBuffer, 16);

	assertTrueThat("Mark is not supported", !is.markSupported());
	log("Buffered echoing from now on (flush on 'f' or every 16 chars)...");
	for (;;) {
		if (is.available() > 0) {
			const unsigned char c = is.read();
			bos.write(c);
			os.write('.');
			if (c == 'f') {
				bos.flush();
			}
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