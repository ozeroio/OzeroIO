#include <Arduino.h>
#include <DataOutput/DataOutput.cpp>
#include <DataOutputStream/DataOutputStream.cpp>
#include <ByteArrayOutputStream/ByteArrayOutputStream.cpp>
#include <FilterOutputStream/FilterOutputStream.cpp>
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
	DataOutputStream dos(&os);

	os.seek(0);
	testWhenSendingEntireBufferSize(&dos, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testWhenSendingOneByOne(&dos, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testWhenSendingParts(&dos, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testNullPointerOrLen0(&dos, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testWriteBeyondLimit(&dos, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testMark(&dos, streamBuffer, sourceBuffer, LEN);
	os.seek(0);
	testWriteSupportedTypes(&dos, streamBuffer, LEN);

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