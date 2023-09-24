#include <Arduino.h>
#include <BufferedOutputStream/BufferedOutputStream.cpp>
#include <External24x256Eeprom/External24x256Eeprom.cpp>
#include <ExternalEepromOutputStream/ExternalEepromOutputStream.cpp>
#include <FilterOutputStream/FilterOutputStream.cpp>
#include <OutputStream/OutputStream.cpp>

#include "../test.cpp"

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 1000
#else
#define LEN 128
#endif

#include <Wire.h>

#define BUFFER_SIZE 32

void setup() {
	Serial.begin(115200);
	Wire.begin();

	Serial.println("Initializing...");

	auto *sourceBuffer = new uint8_t[LEN];
	auto *streamBuffer = new uint8_t[BUFFER_SIZE];

	External24x256Eeprom eeprom(0x00);
	ExternalEepromOutputStream os(&eeprom);
	BufferedOutputStream ebos(&os, streamBuffer, BUFFER_SIZE);

	os.seek(0);
	os.write(0xbb);
	os.flush();
	assertTrueThat("I/O eeprom", eeprom.read(0) == 0xbb);

	os.seek(0);
	testEepromWhenSendingEntireBufferSize(&ebos, &eeprom, sourceBuffer, LEN);
	os.seek(0);
	testEepromWhenSendingOneByOne(&ebos, &eeprom, sourceBuffer, LEN);
	os.seek(0);
	testEepromWhenSendingParts(&ebos, &eeprom, sourceBuffer, LEN);
	os.seek(0);
	testEepromNullPointerOrLen0(&ebos, &eeprom, sourceBuffer, LEN);
	os.seek(0);
	testEepromWriteBeyondLimit(&ebos, &eeprom, sourceBuffer, LEN);
	os.seek(0);
	testEepromMark(&ebos, &eeprom, sourceBuffer, LEN);

	free(sourceBuffer);
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}