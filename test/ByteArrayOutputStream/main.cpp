#include <Arduino.h>
#include <ByteArrayOutputStream/ByteArrayOutputStream.cpp>
#include <OutputStream/OutputStream.cpp>
#include <Wire.h>

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
	randomSeed(analogRead(A0));

	log("Initializing...");

	auto *streamBuffer = new uint8_t[LEN];
	auto *sourceBuffer = new uint8_t[LEN];

	ByteArrayOutputStream os(streamBuffer, LEN);

	os.seek(0);
	testWhenSendingEntireBufferSize(&os, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testWhenSendingOneByOne(&os, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testWhenSendingParts(&os, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testNullPointerOrLen0(&os, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testWriteBeyondLimit(&os, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testMark(&os, streamBuffer, sourceBuffer, LEN);

	free(sourceBuffer);
	free(streamBuffer);
}

void loop() {

#ifdef ARDUINO_ARCH_ESP32
	logPair("Free heap: ", xPortGetFreeHeapSize());
#endif
	delay(1000);
}