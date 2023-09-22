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

bool compareBuffers(uint8_t *a, uint8_t *b, const int len) {
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

void initializeBuffer(uint8_t *buffer, const int len, const bool rand) {
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

void testWhenSendingEntireBufferSize(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testWhenSendingEntireBufferSize");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(sourceBuffer, size, true);
	measureTimeBegin();
	bos->write(sourceBuffer, size);
	bos->flush();
	measureTimeEnd();
	assertTrue(compareBuffers(sourceBuffer, streamBuffer, size));
}

void testWhenSendingParts(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testWhenSendingParts");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(sourceBuffer, size, true);
	measureTimeBegin();

	// Send 8 bytes one by one.
	bos->write(sourceBuffer[0]);
	bos->write(sourceBuffer[1]);
	bos->write(sourceBuffer[2]);
	bos->write(sourceBuffer[3]);
	bos->write(sourceBuffer[4]);
	bos->write(sourceBuffer[5]);
	bos->write(sourceBuffer[6]);
	bos->write(sourceBuffer[7]);

	// Send + 8 bytes.
	bos->write(&sourceBuffer[8], 8);

	// Send + 15 bytes.
	bos->write(&sourceBuffer[16], 15);

	// Send the rest.
	bos->write(&sourceBuffer[31], size - 31);
	bos->flush();

	measureTimeEnd();
	assertTrue(compareBuffers(sourceBuffer, streamBuffer, size));
}

void testWhenSendingOneByOne(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testWhenSendingOneByOne");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(sourceBuffer, size, true);
	measureTimeBegin();
	for (int i = 0; i < size; i++) {
		bos->write(sourceBuffer[i]);
	}
	bos->flush();
	measureTimeEnd();
	assertTrue(compareBuffers(sourceBuffer, streamBuffer, size));
}

void testNullPointerOrLen0(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testNullPointerOrLen0");
	streamBuffer[0] = 0xff;
	sourceBuffer[0] = 0x00;
	bos->write(nullptr, 1);
	bos->write(sourceBuffer, 0);
	assertTrue(streamBuffer[0] == 0xff);
}

void testWriteBeyondLimit(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testWriteBeyondLimit");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(sourceBuffer, size, true);
	bos->write(sourceBuffer, size - 10);
	bos->write(sourceBuffer, 20);
	bos->flush();
	assertTrue(compareBuffers(sourceBuffer, &streamBuffer[size - 10], 10));
}

void testMark(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size) {
	log("testMark");
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(sourceBuffer, size, true);
	const int len = 34;
	bos->write(sourceBuffer, len);
	bos->mark();
	uint8_t a[4] = {0x00, 0x01, 0x02, 0x03};
	bos->write(a, 4);
	bos->reset();
	uint8_t b[4] = {0xab, 0xba, 0xcd, 0xdc};
	bos->write(b, 4);
	bos->flush();
	assertTrue(compareBuffers(&streamBuffer[len], b, 4));
}

void testWhenReadingFully(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size) {
	Serial.println("testWhenReadingFully");
	is->reset();
	is->read(destinationBuffer, size);
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
	is->read(&destinationBuffer[31], size - 31);
}

void testNullPointerOrLen0(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size) {
	log("testNullPointerOrLen0");
	assertTrue(is->read(nullptr, 1) == 0 && is->read(destinationBuffer, 0) == 0);
}

void testReadBeyondLimit(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size) {
	log("testReadBeyondLimit");
	is->reset();
	is->read(destinationBuffer, size - 10);
	auto read = is->read(destinationBuffer, 20) == 10;
	assertTrue(read);
}

void testAvailable(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size) {
	log("testAvailable");
	is->reset();
	is->read();
	auto available = is->available();
	assertTrue(available == size - 1);
	is->read(destinationBuffer, size - 2);
	available = is->available();
	assertTrue(available == 1);
}

void testComparingBuffers(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size, void (*testFunction)(InputStream *, uint8_t *, uint8_t *, int32_t)) {
	initializeBuffer(streamBuffer, size, false);
	initializeBuffer(destinationBuffer, size, true);
	measureTimeBegin();
	testFunction(is, streamBuffer, destinationBuffer, size);
	measureTimeEnd();
	assertTrue(compareBuffers(destinationBuffer, streamBuffer, size));
}

void testWriteSupportedTypes(DataOutput *out, uint8_t *streamBuffer, int32_t size) {
	initializeBuffer(streamBuffer, size, false);
	int n = 0;
	out->write(0xff);
	assertTrue(streamBuffer[n++] == 0xff);
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
	out->writeDouble(-21.1);
	assertTrue(streamBuffer[n++] == 0x9a);
	assertTrue(streamBuffer[n++] == 0x99);
	assertTrue(streamBuffer[n++] == 0x99);
	assertTrue(streamBuffer[n++] == 0x99);
	assertTrue(streamBuffer[n++] == 0x99);
	assertTrue(streamBuffer[n++] == 0x19);
	assertTrue(streamBuffer[n++] == 0x35);
	assertTrue(streamBuffer[n++] == 0xc0);
	out->writeBoolean(false);
	assertTrue(streamBuffer[n++] == 0x00);
	out->writeBoolean(true);
	assertTrue(streamBuffer[n++] == 0x01);
}

void testReadSupportedTypes(DataInput *in, uint8_t *streamBuffer, int32_t size) {
	initializeBuffer(streamBuffer, size, false);
	uint8_t data[] = {
			0xff, 0x00, 0xff, 0x00,
			0x01, 0x06, 0xff, 0x00,
			0xf1, 0xff, 0x7f, 0xb6,
			0xfd, 0xff, 0xff, 0x01,
			0x00, 0xcd, 0xcc, 0xa8,
			0x41, 0xcd, 0xcc, 0xa8,
			0xc1, 0x9a, 0x99, 0x99,
			0x99, 0x99, 0x19, 0x35,
			0xc0, 0x00, 0x01};
	memcpy(streamBuffer, data, sizeof(data));
	assertTrue(in->read() == 0xff);
	assertTrue(in->readInt() == 16842496);
	assertTrue(in->readUnsignedInt() == 4043374342);
	assertTrue(in->readShort() == 32767);
	assertTrue(in->readShort() == -586);
	assertTrue(in->readUnsignedShort() == 65535);
	assertTrue(in->readUnsignedShort() == 1);
	assertTrue(in->readFloat() == 21.1);
	assertTrue(in->readFloat() == -21.1);
	assertTrue(in->readDouble() == -21.1);
	assertTrue(!in->readBoolean());
	assertTrue(in->readBoolean());
}