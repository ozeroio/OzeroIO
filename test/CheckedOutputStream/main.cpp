#include <Arduino.h>
#include <ByteArrayInputStream/ByteArrayInputStream.cpp>
#include <ByteArrayOutputStream/ByteArrayOutputStream.cpp>
#include <CheckedInputStream/CheckedInputStream.cpp>
#include <CheckedOutputStream/CheckedOutputStream.cpp>
#include <Checksum/Checksum.cpp>
#include <CyclicRedundancyChecksum/CyclicRedundancyChecksum.cpp>
#include <FilterOutputStream/FilterOutputStream.cpp>
#include <OutputStream/OutputStream.cpp>

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
	unsigned char outputBuffer[4];
	ByteArrayOutputStream baos(outputBuffer, sizeof(outputBuffer));
	CyclicRedundancyChecksum crc;
	CheckedOutputStream cos(&baos, &crc);

	unsigned char writeBuffer[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE};
	cos.write(writeBuffer, sizeof(writeBuffer));

	// Expected CRC16 result for the updated buffer
	uint16_t expectedCrc = 0xeb93;
	if (crc.getValue() == expectedCrc) {
		Serial.println("CheckedOutputStream test passed with updated buffer!");
	} else {
		Serial.print("CheckedOutputStream test failed! Expected CRC: ");
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