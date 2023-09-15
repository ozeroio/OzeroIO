#include <Arduino.h>
#include <InputStream/InputStream.cpp>
#include <InternalEepromInputStream/InternalEepromInputStream.cpp>

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 512
#else
#define LEN 256
#endif

InternalEepromInputStream eeprom = InternalEepromInputStream();

void setup() {
	Serial.begin(115200);

#ifdef ARDUINO_ARCH_ESP32
	EEPROM.begin(LEN);
#endif

	Serial.println("Initializing...");

	auto *data = new uint8_t[LEN];
	auto *read = new uint8_t[LEN];
	for (int i = 0; i < LEN; i++) {
		auto d = (unsigned char) (random() % 0xff);
		data[i] = d;
		read[i] = 0;
		EEPROM.write(i, d);
	}

#ifdef ARDUINO_ARCH_ESP32
	EEPROM.commit();
#endif

	Serial.print("Read: ");
	uint32_t start = millis();
	eeprom.reset();
	for (int i = 0; i < LEN; i++) {
		read[i] = eeprom.read();
		Serial.println(read[i]);
	}
	Serial.print("Read time: ");
	Serial.println(millis() - start);

	bool match = true;
	for (int i = 0; i < LEN; i++) {
		if (data[i] != read[i]) {
			match = false;
			Serial.print("FAILED! AT ");
			Serial.print(i);
			Serial.print(": data[] = ");
			Serial.print(data[i], HEX);
			Serial.print(", read[] = ");
			Serial.println(read[i], HEX);
		}
	}
	free(data);
	free(read);
	if (match) {
		Serial.println("PASSED!");
	}
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}