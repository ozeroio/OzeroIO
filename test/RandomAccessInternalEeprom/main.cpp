#include <Arduino.h>
#include <DataInput/DataInput.cpp>
#include <DataOutput/DataOutput.cpp>
#include <EEPROM.h>
#include <OutputStream/OutputStream.cpp>
#include <RandomAccessInternalEeprom/RandomAccessInternalEeprom.cpp>

#include "../test.cpp"

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 1000
#else
#define LEN 256
#endif

void setup() {
	Serial.begin(115200);
#ifdef ARDUINO_ARCH_ESP32
	EEPROM.begin(LEN);
#endif

	log("Initializing...");

	RandomAccessInternalEeprom ra(0, 512);

	ra.seek(0);
	ra.write(0xbb);
	assertTrueThat("I/O eeprom", EEPROM.read(0) == 0xbb);

	ra.seek(0);
	uint8_t data[] = {
			0xff,// byte
#ifdef ARDUINO_ARCH_ESP32
			0x00, 0xff, 0x00, 0x01,// int (32 bit)
			0x06, 0xff, 0x00, 0xf1,// uint (32 bit)
#else
			0x00, 0x71,// int (16 bit)
			0x00, 0xf1,// uint (16 bit)
#endif
			0xff, 0x7f,			   // short
			0xb6, 0xfd,			   // short
			0xff, 0xff,			   // u short
			0x01, 0x00,			   // u short
			0x00, 0xe6, 0x2b, 0xf8,// long
			0x00, 0x1a, 0xd4, 0xff,// u long
			0xcd, 0xcc, 0xa8, 0x41,// float
			0xcd, 0xcc, 0xa8, 0xc1,// float

#ifdef ARDUINO_ARCH_ESP32
			0x9a, 0x99, 0x99, 0x99, 0x99, 0x19, 0x35, 0xc0,// double (64 bit)
#else
			0xcd, 0xcc, 0xa8, 0xc1,// double (32 bit)
#endif
			0x00, // bool
			0x01};// bool
#ifdef ARDUINO_ARCH_ESP32
	EEPROM.writeBytes(0, data, sizeof(data));
#else
	for (int i = 0; i < sizeof(data); i++) {
		EEPROM.write(i, data[i]);
	}
#endif
	assertTrue(ra.read() == 0xff);

#ifdef ARDUINO_ARCH_ESP32
	assertTrue(ra.readInt() == 16842496);
	assertTrue(ra.readUnsignedInt() == 4043374342);
#else
	assertTrue(ra.readInt() == 28928);
	assertTrue(ra.readUnsignedInt() == 61696);
#endif
	assertTrue(ra.readShort() == 32767);
	assertTrue(ra.readShort() == -586);
	assertTrue(ra.readUnsignedShort() == 65535);
	assertTrue(ra.readUnsignedShort() == 1);
	assertTrue(ra.readLong() == -131340800);
	assertTrue(ra.readUnsignedLong() == 4292090368);
	assertTrue(ra.readFloat() == (float) 21.1);
	assertTrue(ra.readFloat() == (float) -21.1);
	assertTrue(ra.readDouble() == (double) -21.1);
	assertTrue(!ra.readBoolean());
	assertTrue(ra.readBoolean());

	// Write.
	ra.seek(0);
	int n = 0;
	ra.write(0xff);
	assertTrue(EEPROM.read(n++) == 0xff);
#ifdef ARDUINO_ARCH_ESP32
	ra.writeInt(16842496);
	assertTrue(EEPROM.read(n++) == 0x00);
	assertTrue(EEPROM.read(n++) == 0xff);
	assertTrue(EEPROM.read(n++) == 0x00);
	assertTrue(EEPROM.read(n++) == 0x01);
	ra.writeUnsignedInt(4043374342);
	assertTrue(EEPROM.read(n++) == 0x06);
	assertTrue(EEPROM.read(n++) == 0xff);
	assertTrue(EEPROM.read(n++) == 0x00);
	assertTrue(EEPROM.read(n++) == 0xf1);
#else
	ra.writeInt(28928);
	assertTrue(EEPROM.read(n++) == 0x00);
	assertTrue(EEPROM.read(n++) == 0x71);
	ra.writeUnsignedInt(61696);
	assertTrue(EEPROM.read(n++) == 0x00);
	assertTrue(EEPROM.read(n++) == 0xf1);
#endif
	ra.writeShort(32767);
	assertTrue(EEPROM.read(n++) == 0xff);
	assertTrue(EEPROM.read(n++) == 0x7f);
	ra.writeShort(-586);
	assertTrue(EEPROM.read(n++) == 0xb6);
	assertTrue(EEPROM.read(n++) == 0xfd);
	ra.writeUnsignedShort(65535);
	assertTrue(EEPROM.read(n++) == 0xff);
	assertTrue(EEPROM.read(n++) == 0xff);
	ra.writeUnsignedShort(1);
	assertTrue(EEPROM.read(n++) == 0x01);
	assertTrue(EEPROM.read(n++) == 0x00);
	ra.writeFloat(21.1);
	assertTrue(EEPROM.read(n++) == 0xcd);
	assertTrue(EEPROM.read(n++) == 0xcc);
	assertTrue(EEPROM.read(n++) == 0xa8);
	assertTrue(EEPROM.read(n++) == 0x41);
	// https://www.h-schmidt.net/FloatConverter/IEEE754.html
	ra.writeFloat(-21.1);
	assertTrue(EEPROM.read(n++) == 0xcd);
	assertTrue(EEPROM.read(n++) == 0xcc);
	assertTrue(EEPROM.read(n++) == 0xa8);
	assertTrue(EEPROM.read(n++) == 0xc1);
	// https://www.binaryconvert.com/result_double.html?decimal=045050049046049
#ifdef ARDUINO_ARCH_ESP32
	ra.writeDouble(-21.1);
	assertTrue(EEPROM.read(n++) == 0x9a);
	assertTrue(EEPROM.read(n++) == 0x99);
	assertTrue(EEPROM.read(n++) == 0x99);
	assertTrue(EEPROM.read(n++) == 0x99);
	assertTrue(EEPROM.read(n++) == 0x99);
	assertTrue(EEPROM.read(n++) == 0x19);
	assertTrue(EEPROM.read(n++) == 0x35);
	assertTrue(EEPROM.read(n++) == 0xc0);
#else
	ra.writeDouble(-21.1);
	assertTrue(EEPROM.read(n++) == 0xcd);
	assertTrue(EEPROM.read(n++) == 0xcc);
	assertTrue(EEPROM.read(n++) == 0xa8);
	assertTrue(EEPROM.read(n++) == 0xc1);
#endif
	ra.writeBoolean(false);
	assertTrue(EEPROM.read(n++) == 0x00);
	ra.writeBoolean(true);
	assertTrue(EEPROM.read(n++) == 0x01);
}

void loop() {
#ifdef ARDUINO_ARCH_ESP32
	Serial.print("Free heap: ");
	Serial.println(xPortGetFreeHeapSize());
#endif
	delay(1000);
}