#include <Arduino.h>
#include <ByteArrayInputStream/ByteArrayInputStream.cpp>
#include <DataInput/DataInput.cpp>
#include <DataInputStream/DataInputStream.cpp>
#include <FilterInputStream/FilterInputStream.cpp>
#include <InputStream/InputStream.cpp>

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

	Serial.println("Initializing...");

	auto *streamBuffer = new uint8_t[LEN];
	auto *destinationBuffer = new uint8_t[LEN];

	ByteArrayInputStream is(streamBuffer, LEN);
	DataInputStream dis(&is);

	is.seek(0);
	testInputStreamComparingBuffers(&dis, streamBuffer, destinationBuffer, LEN, testWhenReadingFully);
	is.seek(0);
	testInputStreamComparingBuffers(&dis, streamBuffer, destinationBuffer, LEN, testWhenReadingParts);
	is.seek(0);
	testNullPointerOrLen0(&dis, streamBuffer, destinationBuffer, LEN);
	is.seek(0);
	testReadBeyondLimit(&dis, streamBuffer, destinationBuffer, LEN);
	is.seek(0);
	testAvailable(&dis, streamBuffer, destinationBuffer, LEN);

	is.seek(0);
	testReadSupportedTypes(&dis, streamBuffer, LEN);

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