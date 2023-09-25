#include <Arduino.h>
#include <BufferedOutputStream/BufferedOutputStream.cpp>
#include <FilterOutputStream/FilterOutputStream.cpp>
#include <InternalEepromOutputStream/InternalEepromOutputStream.cpp>
#include <OutputStream/OutputStream.cpp>

#include "../test.cpp"

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 1000
#else
#define LEN 128
#endif

#include <Wire.h>

void setup() {
	Serial.begin(115200);

#ifdef ARDUINO_ARCH_ESP32
	EEPROM.begin(512);
#else
	EEPROM.begin();
#endif

	const int eepromLength = (int) EEPROM.length();

	Serial.println("Initializing...");

	InternalEepromOutputStream os;

	os.seek(0);
	os.write(0xbb);
	os.flush();
	assertTrueThat("I/O beginning of eeprom", EEPROM.read(0) == 0xbb);

	os.seek(eepromLength - 2);
	os.write(0xaa);
	os.flush();
	assertTrueThat("I/O end of eeprom", EEPROM.read(eepromLength - 2) == 0xaa);

	const int n = 4;
	uint8_t b[n] = {0xab, 0xba, 0xcd, 0xdc};
	os.seek(eepromLength - (n - 1));
	os.write(b, n);
	os.flush();
	assertTrueThat("I/O end of eeprom", EEPROM.read(eepromLength - (n - 1)) == 0xab);
	assertTrueThat("I/O end of eeprom", EEPROM.read(eepromLength - (n - 2)) == 0xba);
	assertTrueThat("I/O end of eeprom", EEPROM.read(eepromLength - (n - 3)) == 0xcd);
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}