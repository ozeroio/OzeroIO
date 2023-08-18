#include <Arduino.h>
#include <ExternalEepromOutputStream/ExternalEepromOutputStream.h>
#include <OutputStream/OutputStream.cpp>
#include <RandomAccessByteArray/RandomAccessByteArray.cpp>

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 1000
#else
#define LEN 256
#endif

uint8_t buffer[LEN];
RandomAccessByteArray randomAccess(buffer, LEN);

void setup() {
	Serial.begin(115200);
	Serial.println("Running tests...");
	bool passed = true;
	for (uint32_t i = 898; i < 1000; i++) {
		randomAccess.seek(0);
		randomAccess.writeChar(i);
		randomAccess.writeUnsignedChar(i);
		randomAccess.writeShort(i);
		randomAccess.writeUnsignedShort(i);
		randomAccess.writeInt(i);
		randomAccess.writeUnsignedInt(i);
		randomAccess.writeLong(i);
		randomAccess.writeUnsignedLong(i);
		randomAccess.writeFloat(i);
		randomAccess.writeByte(i);
		randomAccess.writeBoolean(i);
		randomAccess.seek(0);
		if (randomAccess.readChar() != (char) i) {
			Serial.println("readChar failed");
			passed = false;
		}
		if (randomAccess.readUnsignedChar() != (unsigned char) i) {
			Serial.println("readUnsignedChar failed");
			passed = false;
		}
		if (randomAccess.readShort() != (short) i) {
			Serial.println("readShort failed");
			passed = false;
		}
		if (randomAccess.readUnsignedShort() != (unsigned short) i) {
			Serial.println("readUnsignedShort failed");
			passed = false;
		}
		if (randomAccess.readInt() != (int) i) {
			Serial.println("readInt failed");
			passed = false;
		}
		if (randomAccess.readUnsignedInt() != (unsigned int) i) {
			Serial.println("readUnsignedInt failed");
			passed = false;
		}
		if (randomAccess.readLong() != (long) i) {
			Serial.println("readLong failed");
			passed = false;
		}
		if (randomAccess.readUnsignedLong() != (unsigned long) i) {
			Serial.println("readUnsignedLong failed");
			passed = false;
		}
		if (randomAccess.readFloat() != (float) i) {
			Serial.println("readFloat failed");
			passed = false;
		}
		if (randomAccess.readByte() != (byte) i) {
			Serial.println("readByte failed");
			passed = false;
		}
		if (randomAccess.readBoolean() != (bool) i) {
			Serial.println("readBoolean failed");
			passed = false;
		}
	}

	if (passed) {
		Serial.println("PASSED!");
	} else {
		Serial.println("FAILED!");
	}
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}