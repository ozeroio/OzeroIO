#include <Arduino.h>
#include <DataInput/DataInput.cpp>
#include <DataOutput/DataOutput.cpp>
#include <External24x256Eeprom/External24x256Eeprom.h>
#include <ExternalEepromOutputStream/ExternalEepromOutputStream.h>
#include <OutputStream/OutputStream.cpp>
#include <RandomAccessExternalEeprom/RandomAccessExternalEeprom.cpp>
#include <Wire.h>

#include "../test.cpp"

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 1000
#else
#define LEN 256
#endif

void setup() {
	Serial.begin(115200);
	Wire.begin();

	log("Initializing...");

	External24x256Eeprom eeprom(0x00);
	RandomAccessExternalEeprom ra(&eeprom);

	ra.seek(0);
	ra.write(0xbb);
	assertTrueThat("I/O eeprom", eeprom.read(0) == 0xbb);

	ra.seek(0);
	testEepromReadSupportedTypes(&ra, &eeprom, LEN);

	ra.seek(0);
	testEepromWriteSupportedTypes(&ra, &eeprom, LEN);
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}