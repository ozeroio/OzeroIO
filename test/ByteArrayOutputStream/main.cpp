#include <Arduino.h>
#include <Wire.h>
#include <ByteArrayOutputStream/ByteArrayOutputStream.cpp>
#include <OutputStream/OutputStream.cpp>

#include "../test.cpp"

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 1000
#else
#define LEN 128
#endif
#define BUFFER_SIZE 32

void setup() {
	Serial.begin(115200);

	log("Initializing...");

	auto *streamBuffer = new uint8_t[LEN];
	auto *buffer = new uint8_t[BUFFER_SIZE];

	auto *sourceBuffer = new uint8_t[LEN];

	ByteArrayOutputStream os(streamBuffer, LEN);

	os.reset();
	testWhenSendingEntireBufferSize(&os, streamBuffer, sourceBuffer, LEN);
	os.reset();
	testWhenSendingOneByOne(&os, streamBuffer, sourceBuffer, LEN);
	os.reset();
	testWhenSendingParts(&os, streamBuffer, sourceBuffer, LEN);
	os.reset();
	testNullPointerOrLen0(&os, streamBuffer, sourceBuffer, LEN);
	os.reset();
	testWriteBeyondLimit(&os, streamBuffer, sourceBuffer, LEN);
	os.reset();
	testMark(&os, streamBuffer, sourceBuffer, LEN);

	free(sourceBuffer);
	free(buffer);
	free(streamBuffer);
}

void loop() {

#ifdef ESP32
	logPair("Free heap: ", xPortGetFreeHeapSize());
#endif
	delay(1000);
}