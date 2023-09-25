#include <Arduino.h>
#include <DataInput/DataInput.cpp>
#include <DataOutput/DataOutput.cpp>
#include <ExternalEepromOutputStream/ExternalEepromOutputStream.h>
#include <OutputStream/OutputStream.cpp>
#include <RandomAccessByteArray/RandomAccessByteArray.cpp>

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

	auto *streamBuffer = new uint8_t[LEN];

	RandomAccessByteArray ra(streamBuffer, LEN);

	ra.seek(0);
	testReadSupportedTypes(&ra, streamBuffer, LEN);

	ra.seek(0);
	testWriteSupportedTypes(&ra, streamBuffer, LEN);
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}