#include "test.h"

void assertTrue(const bool expression) {
	if (expression == 1) {
		Serial.println("<< PASSED >>");
	} else {
		Serial.println(">> FAILED <<");
	}
}

void assertTrueThat(const char *that, const bool expression) {
	Serial.print(that);
	Serial.print(": ");
	assertTrue(expression);
}

void initializeEeprom(ExternalEeprom *eeprom, const int32_t len, const bool rand) {
	eeprom->setBytes(0, (rand ? random() : 0) & 0xff, len);
}

bool compareBufferToEeprom(uint8_t *a, ExternalEeprom *eeprom, const int32_t len) {
	bool match = true;
	for (int i = 0; i < len; i++) {
		auto read = eeprom->read(i);
		if (a[i] != read) {
			match = false;
			Serial.print(">> FAILED << @ ");
			Serial.print(i);
			Serial.print(": a[] = ");
			Serial.print(a[i], HEX);
			Serial.print(", b[] = ");
			Serial.println(read, HEX);
		}
	}
	return match;
}

bool compareBuffers(uint8_t *a, uint8_t *b, const int32_t len) {
	bool match = true;
	for (int i = 0; i < len; i++) {
		if (a[i] != b[i]) {
			match = false;
			Serial.print(">> FAILED << @ ");
			Serial.print(i);
			Serial.print(": a[] = ");
			Serial.print(a[i], HEX);
			Serial.print(", b[] = ");
			Serial.println(b[i], HEX);
		}
	}
	return match;
}

void initializeBuffer(uint8_t *buffer, const int32_t len, const bool rand) {
	if (rand) {
		for (int i = 0; i < len; i++) {
			buffer[i] = random() % 0xff;
		}
	} else {
		memset(buffer, 0x00, len);
	}
}

void measureTimeBegin() {
	prevTime = millis();
}

void measureTimeEnd() {
	logPair((const char *) "Time measure: ", millis() - prevTime);
}

void log(const char *msg) {
	Serial.println(msg);
}

void logPair(const char *key, uint32_t value) {
	Serial.print(key);
	Serial.println(value);
}

void testWhenSendingEntireBufferSize(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testWhenSendingEntireBufferSize");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(sourceBuffer, size, true);
	measureTimeBegin();
	os->write(sourceBuffer, (int) size);
	os->flush();
	measureTimeEnd();
	assertTrue(compareBuffers(sourceBuffer, streamBuffer, size));
}

void testEepromWhenSendingEntireBufferSize(OutputStream *os, ExternalEeprom *eeprom, uint8_t *sourceBuffer, int32_t size) {
	log("testEepromWhenSendingEntireBufferSize");
	initializeEeprom(eeprom, size, false);
	initializeBuffer(sourceBuffer, size, true);
	measureTimeBegin();
	os->write(sourceBuffer, (int) size);
	os->flush();
	measureTimeEnd();
	measureTimeBegin();
	assertTrueThat("Buffer matches eeprom", compareBufferToEeprom(sourceBuffer, eeprom, size));
	measureTimeEnd();
}

void writeParts(OutputStream *os, uint8_t *sourceBuffer, int32_t size) {
	log("writeParts");
	measureTimeBegin();

	// Send 8 bytes one by one.
	os->write(sourceBuffer[0]);
	os->write(sourceBuffer[1]);
	os->write(sourceBuffer[2]);
	os->write(sourceBuffer[3]);
	os->write(sourceBuffer[4]);
	os->write(sourceBuffer[5]);
	os->write(sourceBuffer[6]);
	os->write(sourceBuffer[7]);

	// Send + 8 bytes.
	os->write(&sourceBuffer[8], 8);

	// Send + 15 bytes.
	os->write(&sourceBuffer[16], 15);

	// Send the rest.
	os->write(&sourceBuffer[31], (int) size - 31);
	os->flush();

	measureTimeEnd();
}

void testWhenSendingParts(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testWhenSendingParts");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(sourceBuffer, size, true);
	writeParts(os, sourceBuffer, size);
	measureTimeBegin();
	assertTrueThat("Buffers match", compareBuffers(sourceBuffer, streamBuffer, size));
	measureTimeEnd();
}

void testEepromWhenSendingParts(OutputStream *os, ExternalEeprom *eeprom, uint8_t *sourceBuffer, int32_t size) {
	log("testEepromWhenSendingParts");
	initializeEeprom(eeprom, size, false);
	initializeBuffer(sourceBuffer, size, true);
	writeParts(os, sourceBuffer, size);
	measureTimeBegin();
	assertTrueThat("Buffer matches eeprom", compareBufferToEeprom(sourceBuffer, eeprom, size));
	measureTimeEnd();
}

void testWhenSendingOneByOne(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testWhenSendingOneByOne");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(sourceBuffer, size, true);
	measureTimeBegin();
	for (int32_t i = 0; i < size; i++) {
		os->write(sourceBuffer[i]);
	}
	os->flush();
	measureTimeEnd();
	assertTrue(compareBuffers(sourceBuffer, streamBuffer, size));
}

void testEepromWhenSendingOneByOne(OutputStream *os, ExternalEeprom *eeprom, uint8_t *sourceBuffer, int32_t size) {
	log("testEepromWhenSendingOneByOne");
	initializeEeprom(eeprom, size, false);
	initializeBuffer(sourceBuffer, size, true);
	measureTimeBegin();
	for (int32_t i = 0; i < size; i++) {
		os->write(sourceBuffer[i]);
	}
	os->flush();
	measureTimeEnd();
	measureTimeBegin();
	assertTrueThat("Buffer matches eeprom", compareBufferToEeprom(sourceBuffer, eeprom, size));
	measureTimeEnd();
}

void testNullPointerOrLen0(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testNullPointerOrLen0");
	streamBuffer[0] = 0xff;
	sourceBuffer[0] = 0x00;
	os->write(nullptr, 1);
	os->write(sourceBuffer, 0);
	assertTrue(streamBuffer[0] == 0xff);
}

void testEepromNullPointerOrLen0(OutputStream *os, ExternalEeprom *eeprom, uint8_t *sourceBuffer, int32_t size) {
	log("testEepromNullPointerOrLen0");
	eeprom->write(0, 0xff);
	sourceBuffer[0] = 0x00;
	os->write(nullptr, 1);
	os->write(sourceBuffer, 0);
	assertTrue(eeprom->read(0) == 0xff);
}

void testWriteBeyondLimit(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testWriteBeyondLimit");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(sourceBuffer, size, true);
	os->write(sourceBuffer, (int) size - 10);
	os->write(sourceBuffer, 20);
	os->flush();
	assertTrue(compareBuffers(sourceBuffer, &streamBuffer[size - 10], 10));
}

void testEepromWriteBeyondLimit(OutputStream *os, ExternalEeprom *eeprom, uint8_t *sourceBuffer, int32_t size) {
	log("testEepromWriteBeyondLimit");
	initializeEeprom(eeprom, size, false);
	initializeBuffer(sourceBuffer, size, true);
	os->write(sourceBuffer, (int) size - 10);
	os->write(sourceBuffer, 20);
	os->flush();
	measureTimeBegin();
	uint8_t b[10] = {0};
	eeprom->readBytes(size - 10, b, 10);
	assertTrueThat("Buffer matches eeprom", compareBuffers(sourceBuffer, b, 10));
	measureTimeEnd();
}

void testMark(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testMark");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(sourceBuffer, size, true);
	const int len = 34;
	os->write(sourceBuffer, len);
	os->mark();
	uint8_t a[4] = {0x00, 0x01, 0x02, 0x03};
	os->write(a, 4);
	os->reset();
	uint8_t b[4] = {0xab, 0xba, 0xcd, 0xdc};
	os->write(b, 4);
	os->flush();
	assertTrue(compareBuffers(&streamBuffer[len], b, 4));
}

void testEepromMark(OutputStream *os, ExternalEeprom *eeprom, uint8_t *sourceBuffer, int32_t size) {
	log("testMark");
	initializeEeprom(eeprom, size, false);
	initializeBuffer(sourceBuffer, size, true);
	const int len = 34;

	// Write `len` of date to the stream.
	os->write(sourceBuffer, len);

	// Mark it.
	os->mark();

	// White an array to stream.
	uint8_t a[4] = {0x00, 0x01, 0x02, 0x03};
	os->write(a, 4);

	// Read the same written size from the eeprom.
	uint8_t r[4] = {0};
	eeprom->readBytes(len, r, 4);

	// It must be equals to `a`.
	assertTrue(compareBuffers(r, a, 4));

	// Reset and write `b` instead.
	os->reset();
	uint8_t b[4] = {0xab, 0xba, 0xcd, 0xdc};
	os->write(b, 4);
	os->flush();

	// Read it again now, after resetting.
	eeprom->readBytes(len, r, 4);

	// It must be equals to `b` now.
	assertTrue(compareBuffers(r, b, 4));
}

void testWhenReadingFully(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size) {
	Serial.println("testWhenReadingFully");
	is->reset();
	is->read(destinationBuffer, (int) size);
}

void testWhenReadingParts(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size) {
	Serial.println("testWhenReadingParts");

	is->reset();

	is->read(&destinationBuffer[0], 1);
	is->read(&destinationBuffer[1], 1);
	is->read(&destinationBuffer[2], 1);
	is->read(&destinationBuffer[3], 1);
	is->read(&destinationBuffer[4], 1);
	is->read(&destinationBuffer[5], 1);
	is->read(&destinationBuffer[6], 1);
	is->read(&destinationBuffer[7], 1);

	is->read(&destinationBuffer[8], 8);
	is->read(&destinationBuffer[16], 15);
	is->read(&destinationBuffer[31], (int) size - 31);
}

void testNullPointerOrLen0(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size) {
	log("testNullPointerOrLen0");
	assertTrue(is->read(nullptr, 1) == 0 && is->read(destinationBuffer, 0) == 0);
}

void testReadBeyondLimit(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size) {
	log("testReadBeyondLimit");
	is->reset();
	is->read(destinationBuffer, (int) size - 10);
	auto read = is->read(destinationBuffer, 20) == 10;
	assertTrue(read);
}

void testAvailable(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size) {
	log("testAvailable");
	is->reset();
	is->read();
	auto available = is->available();
	assertTrue(available == size - 1);
	is->read(destinationBuffer, (int) size - 2);
	available = is->available();
	assertTrue(available == 1);
}

void testInputStreamComparingBuffers(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size, void (*testFunction)(InputStream *, uint8_t *, uint8_t *, int32_t)) {
	log("testInputStreamComparingBuffers");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(destinationBuffer, size, true);
	measureTimeBegin();
	testFunction(is, streamBuffer, destinationBuffer, size);
	measureTimeEnd();
	assertTrue(compareBuffers(destinationBuffer, streamBuffer, size));
}

void testWriteSupportedTypes(DataOutput *out, uint8_t *streamBuffer, int32_t size) {
	log("testWriteSupportedTypes");
	initializeBuffer(streamBuffer, size, false);
	int n = 0;
	out->write(0xff);
	assertTrue(streamBuffer[n++] == 0xff);
#ifdef ARDUINO_ARCH_ESP32
	out->writeInt(16842496);
	assertTrue(streamBuffer[n++] == 0x00);
	assertTrue(streamBuffer[n++] == 0xff);
	assertTrue(streamBuffer[n++] == 0x00);
	assertTrue(streamBuffer[n++] == 0x01);
	out->writeUnsignedInt(4043374342);
	assertTrue(streamBuffer[n++] == 0x06);
	assertTrue(streamBuffer[n++] == 0xff);
	assertTrue(streamBuffer[n++] == 0x00);
	assertTrue(streamBuffer[n++] == 0xf1);
#else
	out->writeInt(28928);
	assertTrue(streamBuffer[n++] == 0x00);
	assertTrue(streamBuffer[n++] == 0x71);
	out->writeUnsignedInt(61696);
	assertTrue(streamBuffer[n++] == 0x00);
	assertTrue(streamBuffer[n++] == 0xf1);
#endif
	out->writeShort(32767);
	assertTrue(streamBuffer[n++] == 0xff);
	assertTrue(streamBuffer[n++] == 0x7f);
	out->writeShort(-586);
	assertTrue(streamBuffer[n++] == 0xb6);
	assertTrue(streamBuffer[n++] == 0xfd);
	out->writeUnsignedShort(65535);
	assertTrue(streamBuffer[n++] == 0xff);
	assertTrue(streamBuffer[n++] == 0xff);
	out->writeUnsignedShort(1);
	assertTrue(streamBuffer[n++] == 0x01);
	assertTrue(streamBuffer[n++] == 0x00);
	out->writeFloat(21.1);
	assertTrue(streamBuffer[n++] == 0xcd);
	assertTrue(streamBuffer[n++] == 0xcc);
	assertTrue(streamBuffer[n++] == 0xa8);
	assertTrue(streamBuffer[n++] == 0x41);
	// https://www.h-schmidt.net/FloatConverter/IEEE754.html
	out->writeFloat(-21.1);
	assertTrue(streamBuffer[n++] == 0xcd);
	assertTrue(streamBuffer[n++] == 0xcc);
	assertTrue(streamBuffer[n++] == 0xa8);
	assertTrue(streamBuffer[n++] == 0xc1);
	// https://www.binaryconvert.com/result_double.html?decimal=045050049046049
#ifdef ARDUINO_ARCH_ESP32
	out->writeDouble(-21.1);
	assertTrue(streamBuffer[n++] == 0x9a);
	assertTrue(streamBuffer[n++] == 0x99);
	assertTrue(streamBuffer[n++] == 0x99);
	assertTrue(streamBuffer[n++] == 0x99);
	assertTrue(streamBuffer[n++] == 0x99);
	assertTrue(streamBuffer[n++] == 0x19);
	assertTrue(streamBuffer[n++] == 0x35);
	assertTrue(streamBuffer[n++] == 0xc0);
#else
	out->writeDouble(-21.1);
	assertTrue(streamBuffer[n++] == 0xcd);
	assertTrue(streamBuffer[n++] == 0xcc);
	assertTrue(streamBuffer[n++] == 0xa8);
	assertTrue(streamBuffer[n++] == 0xc1);
#endif
	out->writeBoolean(false);
	assertTrue(streamBuffer[n++] == 0x00);
	out->writeBoolean(true);
	assertTrue(streamBuffer[n++] == 0x01);
}

void testEepromWriteSupportedTypes(DataOutput *out, ExternalEeprom *eeprom, int32_t size) {
	log("testWriteSupportedTypes");
	initializeEeprom(eeprom, size, false);
	int n = 0;
	out->write(0xff);
	assertTrue(eeprom->read(n++) == 0xff);
#ifdef ARDUINO_ARCH_ESP32
	out->writeInt(16842496);
	assertTrue(eeprom->read(n++) == 0x00);
	assertTrue(eeprom->read(n++) == 0xff);
	assertTrue(eeprom->read(n++) == 0x00);
	assertTrue(eeprom->read(n++) == 0x01);
	out->writeUnsignedInt(4043374342);
	assertTrue(eeprom->read(n++) == 0x06);
	assertTrue(eeprom->read(n++) == 0xff);
	assertTrue(eeprom->read(n++) == 0x00);
	assertTrue(eeprom->read(n++) == 0xf1);
#else
	out->writeInt(28928);
	assertTrue(eeprom->read(n++) == 0x00);
	assertTrue(eeprom->read(n++) == 0x71);
	out->writeUnsignedInt(61696);
	assertTrue(eeprom->read(n++) == 0x00);
	assertTrue(eeprom->read(n++) == 0xf1);
#endif
	out->writeShort(32767);
	assertTrue(eeprom->read(n++) == 0xff);
	assertTrue(eeprom->read(n++) == 0x7f);
	out->writeShort(-586);
	assertTrue(eeprom->read(n++) == 0xb6);
	assertTrue(eeprom->read(n++) == 0xfd);
	out->writeUnsignedShort(65535);
	assertTrue(eeprom->read(n++) == 0xff);
	assertTrue(eeprom->read(n++) == 0xff);
	out->writeUnsignedShort(1);
	assertTrue(eeprom->read(n++) == 0x01);
	assertTrue(eeprom->read(n++) == 0x00);
	out->writeFloat(21.1);
	assertTrue(eeprom->read(n++) == 0xcd);
	assertTrue(eeprom->read(n++) == 0xcc);
	assertTrue(eeprom->read(n++) == 0xa8);
	assertTrue(eeprom->read(n++) == 0x41);
	// https://www.h-schmidt.net/FloatConverter/IEEE754.html
	out->writeFloat(-21.1);
	assertTrue(eeprom->read(n++) == 0xcd);
	assertTrue(eeprom->read(n++) == 0xcc);
	assertTrue(eeprom->read(n++) == 0xa8);
	assertTrue(eeprom->read(n++) == 0xc1);
	// https://www.binaryconvert.com/result_double.html?decimal=045050049046049
#ifdef ARDUINO_ARCH_ESP32
	out->writeDouble(-21.1);
	assertTrue(eeprom->read(n++) == 0x9a);
	assertTrue(eeprom->read(n++) == 0x99);
	assertTrue(eeprom->read(n++) == 0x99);
	assertTrue(eeprom->read(n++) == 0x99);
	assertTrue(eeprom->read(n++) == 0x99);
	assertTrue(eeprom->read(n++) == 0x19);
	assertTrue(eeprom->read(n++) == 0x35);
	assertTrue(eeprom->read(n++) == 0xc0);
#else
	out->writeDouble(-21.1);
	assertTrue(eeprom->read(n++) == 0xcd);
	assertTrue(eeprom->read(n++) == 0xcc);
	assertTrue(eeprom->read(n++) == 0xa8);
	assertTrue(eeprom->read(n++) == 0xc1);
#endif
	out->writeBoolean(false);
	assertTrue(eeprom->read(n++) == 0x00);
	out->writeBoolean(true);
	assertTrue(eeprom->read(n++) == 0x01);
}

void testReadSupportedTypes(DataInput *in, uint8_t *streamBuffer, int32_t size) {
	log("testReadSupportedTypes");
	initializeBuffer(streamBuffer, size, false);
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
	memcpy(streamBuffer, data, sizeof(data));
	assertTrue(in->read() == 0xff);
#ifdef ARDUINO_ARCH_ESP32
	assertTrue(in->readInt() == 16842496);
	assertTrue(in->readUnsignedInt() == 4043374342);
#else
	assertTrue(in->readInt() == 28928);
	assertTrue(in->readUnsignedInt() == 61696);
#endif
	assertTrue(in->readShort() == 32767);
	assertTrue(in->readShort() == -586);
	assertTrue(in->readUnsignedShort() == 65535);
	assertTrue(in->readUnsignedShort() == 1);
	assertTrue(in->readLong() == -131340800);
	assertTrue(in->readUnsignedLong() == 4292090368);
	assertTrue(in->readFloat() == (float) 21.1);
	assertTrue(in->readFloat() == (float) -21.1);
	assertTrue(in->readDouble() == (double) -21.1);
	assertTrue(!in->readBoolean());
	assertTrue(in->readBoolean());
}

void testEepromReadSupportedTypes(DataInput *in, ExternalEeprom *eeprom, int32_t size) {
	log("testReadSupportedTypes");
	initializeEeprom(eeprom, size, false);
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
	eeprom->writeBytes(0, data, sizeof(data));
	assertTrue(in->read() == 0xff);
#ifdef ARDUINO_ARCH_ESP32
	assertTrue(in->readInt() == 16842496);
	assertTrue(in->readUnsignedInt() == 4043374342);
#else
	assertTrue(in->readInt() == 28928);
	assertTrue(in->readUnsignedInt() == 61696);
#endif
	assertTrue(in->readShort() == 32767);
	assertTrue(in->readShort() == -586);
	assertTrue(in->readUnsignedShort() == 65535);
	assertTrue(in->readUnsignedShort() == 1);
	assertTrue(in->readLong() == -131340800);
	assertTrue(in->readUnsignedLong() == 4292090368);
	assertTrue(in->readFloat() == (float) 21.1);
	assertTrue(in->readFloat() == (float) -21.1);
	assertTrue(in->readDouble() == (double) -21.1);
	assertTrue(!in->readBoolean());
	assertTrue(in->readBoolean());
}