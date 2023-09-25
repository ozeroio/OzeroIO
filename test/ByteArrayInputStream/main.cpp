#include <Arduino.h>
#include <ByteArrayInputStream/ByteArrayInputStream.cpp>
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

	Serial.println("Initializing...");

	auto *streamBuffer = new uint8_t[LEN];
	auto *destinationBuffer = new uint8_t[LEN];

	ByteArrayInputStream is(streamBuffer, LEN);

	is.reset();
	testInputStreamComparingBuffers(&is, streamBuffer, destinationBuffer, LEN, testWhenReadingFully);
	is.reset();
	testInputStreamComparingBuffers(&is, streamBuffer, destinationBuffer, LEN, testWhenReadingParts);
	is.reset();
	testNullPointerOrLen0(&is, streamBuffer, destinationBuffer, LEN);
	is.reset();
	testReadBeyondLimit(&is, streamBuffer, destinationBuffer, LEN);
	is.reset();
	testAvailable(&is, streamBuffer, destinationBuffer, LEN);

	free(destinationBuffer);
	free(streamBuffer);
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(10000);
}