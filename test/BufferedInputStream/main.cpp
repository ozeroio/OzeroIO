#include <Arduino.h>
#include <BufferedInputStream/BufferedInputStream.cpp>
#include <ByteArrayInputStream/ByteArrayInputStream.cpp>
#include <FilterInputStream/FilterInputStream.cpp>
#include <InputStream/InputStream.cpp>

#include "../test.cpp"

#ifdef ESP32
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
	auto *destinationBuffer = new uint8_t[LEN];
	auto *buffer = new uint8_t[BUFFER_SIZE];

	ByteArrayInputStream is(streamBuffer, LEN);
	BufferedInputStream bis(&is, buffer, BUFFER_SIZE);

	is.reset();
	testInputStreamComparingBuffers(&bis, streamBuffer, destinationBuffer, LEN, testWhenReadingFully);
	is.reset();
	testInputStreamComparingBuffers(&bis, streamBuffer, destinationBuffer, LEN, testWhenReadingParts);
	is.reset();
	testNullPointerOrLen0(&bis, streamBuffer, destinationBuffer, LEN);
	is.reset();
	testReadBeyondLimit(&bis, streamBuffer, destinationBuffer, LEN);
	is.reset();
	testAvailable(&bis, streamBuffer, destinationBuffer, LEN);

	free(destinationBuffer);
	free(streamBuffer);
}

void loop() {

#ifdef ESP32
	logPair("Free heap: ", xPortGetFreeHeapSize());
#endif
	delay(10000);
}