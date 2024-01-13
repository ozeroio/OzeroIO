#include <Arduino.h>
#include <External24x256Eeprom/External24x256Eeprom.h>
#include <ExternalEepromInputStream/ExternalEepromInputStream.cpp>
#include <ExternalEepromInputStream/ExternalEepromInputStream.h>
#include <InputStream/InputStream.cpp>
#include <Wire.h>

#include "../test.cpp"

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 10000
#else
#define LEN 256
#endif

void setup() {
	Serial.begin(115200);
#ifdef ARDUINO_ARCH_ESP32
	Wire.begin(27, 26);
#else
	Wire.begin();
#endif
	Serial.println("Initializing...");

	auto *destinationBuffer = new uint8_t[LEN];
	auto *streamBuffer = new uint8_t[LEN];

	External24x256Eeprom eeprom(0x00);
	ExternalEepromInputStream is(&eeprom);

	// Initialize a buffer randomly.
	initializeBuffer(streamBuffer, LEN, false);

	// Write the buffer to the EEPROM.
	for (int32_t i = 0; i < LEN; i++) {
		eeprom.write(i, streamBuffer[i]);
	}

	is.reset();
	testInputStreamComparingBuffers(&is, streamBuffer, destinationBuffer, LEN, testWhenReadingFully);
	is.reset();
	testInputStreamComparingBuffers(&is, streamBuffer, destinationBuffer, LEN, testWhenReadingParts);
	is.reset();
	testReadBeyondLimit(&is, streamBuffer, destinationBuffer, LEN);
	is.reset();
	testAvailable(&is, streamBuffer, destinationBuffer, LEN);
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}