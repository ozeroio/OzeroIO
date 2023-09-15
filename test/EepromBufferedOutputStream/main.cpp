#include <Arduino.h>
#include <BufferedOutputStream/BufferedOutputStream.cpp>
#include <External24x256Eeprom/External24x256Eeprom.cpp>
#include <ExternalEepromOutputStream/ExternalEepromOutputStream.cpp>
#include <FilterOutputStream/FilterOutputStream.cpp>
#include <OutputStream/OutputStream.cpp>

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 4000
#else
#define LEN 128
#endif

#include <Wire.h>

#define BUFFER_SIZE 32

void initializeBuffers(ExternalEeprom *eeprom, uint8_t *data) {
	for (int i = 0; i < LEN; i++) {
		data[i] = random() % 0xff;
	}
	eeprom->setBytes(0, 0, LEN);
}

bool compareBuffers(uint8_t *a, ExternalEeprom *eeprom) {
	bool match = true;
	for (int i = 0; i < LEN; i++) {
		auto read = eeprom->read(i);
		if (a[i] != read) {
			match = false;
			Serial.print("FAILED! AT ");
			Serial.print(i);
			Serial.print(": a[] = ");
			Serial.print(a[i], HEX);
			Serial.print(", b[] = ");
			Serial.println(read, HEX);
		}
	}
	return match;
}

void testWhenSendingEntireBufferSize(OutputStream *bos, ExternalEeprom *eeprom, uint8_t *data) {
	Serial.println("testWhenSendingEntireBufferSize");

	uint32_t start = millis();
	initializeBuffers(eeprom, data);
	Serial.print("It took to initialize the buffer: ");
	Serial.println(millis() - start);

	start = millis();

	bos->reset();
	bos->write(data, LEN);
	bos->flush();

	Serial.print("It took to run: ");
	Serial.println(millis() - start);

	start = millis();
	if (compareBuffers(data, eeprom)) {
		Serial.println("PASSED!");
	} else {
		Serial.println("FAILED!");
	}
	Serial.print("It took to compare: ");
	Serial.println(millis() - start);
}

void testWhenSendingParts(OutputStream *bos, ExternalEeprom *eeprom, uint8_t *data) {
	Serial.println("testWhenSendingParts");

	uint32_t start = millis();
	initializeBuffers(eeprom, data);
	Serial.print("It took to initialize the buffer: ");
	Serial.println(millis() - start);

	start = millis();

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

	for (int i = 31; i < LEN/2; i++) {
		bos->write(data[i]);
	}

	// Send the rest.
	bos->write(&data[LEN/2], LEN/2);

	bos->flush();

	Serial.print("It took to run: ");
	Serial.println(millis() - start);

	start = millis();
	if (compareBuffers(data, eeprom)) {
		Serial.println("PASSED!");
	} else {
		Serial.println("FAILED!");
	}
	Serial.print("It took to compare: ");
	Serial.println(millis() - start);
}

void setup() {
	Serial.begin(115200);
	Wire.begin();

	Serial.println("Initializing...");

	auto *buffer = new uint8_t[BUFFER_SIZE];

	auto *data = new uint8_t[LEN];

	External24x256Eeprom eeprom(0x00);

	ExternalEepromOutputStream os(&eeprom);
	BufferedOutputStream bos(&os, buffer, BUFFER_SIZE);

	Serial.println("Without buffer: ");
	testWhenSendingEntireBufferSize(&os, &eeprom, data);
	testWhenSendingParts(&os, &eeprom, data);

	Serial.println("With buffer: ");
	testWhenSendingEntireBufferSize(&bos, &eeprom, data);
	testWhenSendingParts(&bos, &eeprom, data);

	free(data);
	free(buffer);
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}