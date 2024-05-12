#include <Arduino.h>
#include <AsyncBufferedOutputStream/AsyncBufferedOutputStream.cpp>
#include <BufferedOutputStream/BufferedOutputStream.cpp>
#include <ByteArrayOutputStream/ByteArrayOutputStream.cpp>
#include <FilterOutputStream/FilterOutputStream.cpp>
#include <OutputStream/OutputStream.cpp>

#include "../test.cpp"

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 257
#else
#define LEN 128
#endif
#define BUFFER_SIZE 31

void setup() {
	Serial.begin(115200);

	log("Initializing...");
	auto *streamBuffer = new uint8_t[LEN];
	auto *buffer = new uint8_t[BUFFER_SIZE];

	auto *sourceBuffer = new uint8_t[LEN];

	ByteArrayOutputStream os(streamBuffer, LEN);
	AsyncBufferedOutputStream bos(&os, buffer, BUFFER_SIZE);

	os.reset();
	testWhenSendingEntireBufferSize(&bos, streamBuffer, sourceBuffer, LEN);
	os.reset();
	testWhenSendingOneByOne(&bos, streamBuffer, sourceBuffer, LEN);
	os.reset();
	testWhenSendingParts(&bos, streamBuffer, sourceBuffer, LEN);
	os.reset();
	testNullPointerOrLen0(&bos, streamBuffer, sourceBuffer, LEN);
	os.reset();
	testWriteBeyondLimit(&bos, streamBuffer, sourceBuffer, LEN);
	os.reset();
	testMark(&bos, streamBuffer, sourceBuffer, LEN);

	free(sourceBuffer);
	free(buffer);
	free(streamBuffer);
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	logPair("Free heap: ", xPortGetFreeHeapSize());
#endif
	vTaskDelay(1000 / portTICK_PERIOD_MS);
}