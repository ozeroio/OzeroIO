#include <Arduino.h>
#include <BufferedOutputStream/BufferedOutputStream.cpp>
#include <OutputStream/OutputStream.cpp>
#include <FilterOutputStream/FilterOutputStream.cpp>
#include <ByteArrayOutputStream/ByteArrayOutputStream.cpp>
#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 1000
#else
#define LEN 128
#endif
#define BUFFER_SIZE 32

void initializeBuffers(uint8_t *byteArray, uint8_t *data) {
	for (int i = 0; i < LEN; i++) {
		data[i] = random() % 0xff;
		byteArray[i] = 0;
	}
}

bool compareBuffers(uint8_t *a, uint8_t *b) {
	bool match = true;
	for (int i = 0; i < LEN; i++) {
		if (a[i] != b[i]) {
			match = false;
			Serial.print("FAILED! AT ");
			Serial.print(i);
			Serial.print(": a[] = ");
			Serial.print(a[i], HEX);
			Serial.print(", b[] = ");
			Serial.println(b[i], HEX);
		}
	}
	return match;
}

void testWhenSendingEntireBufferSize(OutputStream *bos, uint8_t *byteArray, uint8_t *data) {
	initializeBuffers(byteArray, data);
	Serial.println("testWhenSendingEntireBufferSize");
	uint32_t start = millis();

	bos->reset();
	bos->write(data, LEN);
	bos->flush();

	Serial.print("It took: ");
	Serial.println(millis() - start);

	if (compareBuffers(data, byteArray)) {
		Serial.println("PASSED!");
	} else {
		Serial.println("FAILED!");
	}
}

void testWhenSendingParts(OutputStream *bos, uint8_t *byteArray, uint8_t *data) {
	initializeBuffers(byteArray, data);
	Serial.println("testWhenSendingParts");
	uint32_t start = millis();

	bos->reset();

	// Send 8 bytes one by one.
	bos->write(data[0]);
	bos->write(data[1]);
	bos->write(data[2]);
	bos->write(data[3]);
	bos->write(data[4]);
	bos->write(data[5]);
	bos->write(data[6]);
	bos->write(data[7]);

	// Send + 8 bytes.
	bos->write(&data[8], 8);

	// Send + 15 bytes.
	bos->write(&data[16], 15);

	// Send the rest.
	bos->write(&data[31], LEN - 31);

	bos->flush();

	Serial.print("It took: ");
	Serial.println(millis() - start);

	if (compareBuffers(data, byteArray)) {
		Serial.println("PASSED!");
	} else {
		Serial.println("FAILED!");
	}
}

void setup() {
	Serial.begin(115200);

	Serial.println("Initializing...");

	auto *byteArray = new uint8_t[LEN];
	auto *buffer = new uint8_t[BUFFER_SIZE];

	auto *data = new uint8_t[LEN];

	ByteArrayOutputStream os(byteArray, LEN);
	BufferedOutputStream bos(&os, buffer, BUFFER_SIZE);

	testWhenSendingEntireBufferSize(&bos, byteArray, data);
	testWhenSendingParts(&bos, byteArray, data);

	free(data);
	free(buffer);
	free(byteArray);
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}