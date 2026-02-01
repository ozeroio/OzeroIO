#include <Arduino.h>
#include <ByteArrayInputStream/ByteArrayInputStream.cpp>
#include <CheckedInputStream/CheckedInputStream.cpp>
#include <Checksum/Checksum.cpp>
#include <CyclicRedundancyChecksum/CyclicRedundancyChecksum.cpp>
#include <FilterInputStream/FilterInputStream.cpp>
#include <InputStream/InputStream.cpp>

#include "../test.cpp"

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 257
#else
#define LEN 128
#endif
#define BUFFER_SIZE 31

void setup() {
	Serial.begin(115200);

	log("Initializing...");
	unsigned char inputBuffer[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE};
	ByteArrayInputStream bais(inputBuffer, sizeof(inputBuffer));
	CyclicRedundancyChecksum crc;
	CheckedInputStream cis(&bais, &crc);

	unsigned char readBuffer[8];
	int bytesRead = cis.read(readBuffer, sizeof(readBuffer));

	// Expected CRC16 result for the input buffer
	uint16_t expectedCrc = 0xeb93;
	if (bytesRead == sizeof(inputBuffer)) {
		Serial.println("Read all bytes successfully.");
	} else {
		Serial.print("Failed to read all bytes. Bytes read: ");
		Serial.println(bytesRead);
	}
	if (crc.getValue() == expectedCrc) {
		Serial.println("CheckedInputStream test passed with expected CRC!");
	} else {
		Serial.print("CheckedInputStream test failed! Expected CRC: ");
		Serial.print(expectedCrc, HEX);
		Serial.print(", but got: ");
		Serial.println(crc.getValue(), HEX);
	}
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	logPair("Free heap: ", xPortGetFreeHeapSize());
#endif
	vTaskDelay(1000 / portTICK_PERIOD_MS);
}