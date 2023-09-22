#if OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "RandomAccessInternalEeprom.h"
#include <EEPROM.h>

RandomAccessInternalEeprom::RandomAccessInternalEeprom(int startPos, int endPos) : pos(startPos),
																				   startPos(startPos),
																				   endPos(endPos),
																				   size(endPos - startPos) {
}

int RandomAccessInternalEeprom::length() const {
	return size;
}

void RandomAccessInternalEeprom::seek(int pos) {
	if (pos >= size) {
		pos = size - 1;
	}
	this->pos = startPos + pos;
}

void RandomAccessInternalEeprom::close() {
}

void RandomAccessInternalEeprom::write(unsigned char *b, const int len) {
	writeBytes(b, len);
}

void RandomAccessInternalEeprom::write(const unsigned char b) {
	writeByte(b);
}

void RandomAccessInternalEeprom::writeByte(const unsigned char b) {
	writeBytes((unsigned char *) &b, 1);
}

void RandomAccessInternalEeprom::writeBytes(unsigned char *b, int len) {
	if (pos + len >= endPos) {
		len = endPos - pos;
	}
#ifdef ESP32
	int written = EEPROM.writeBytes(pos, (void *) b, len);
	EEPROM.commit();
	pos += written;
#else
	for (int i = 0; i < len; i++) {
		EEPROM.write(pos++, b[i]);
	}
#endif
}

void RandomAccessInternalEeprom::writeBoolean(const bool v) {
	writeBytes((unsigned char *) &v, 1);
}

void RandomAccessInternalEeprom::writeChar(const char c) {
	writeBytes((unsigned char *) &c, 1);
}

void RandomAccessInternalEeprom::writeUnsignedChar(const unsigned char c) {
	writeBytes((unsigned char *) &c, 1);
}

void RandomAccessInternalEeprom::writeShort(const short v) {
	writeBytes((unsigned char *) &v, sizeof(short));
}

void RandomAccessInternalEeprom::writeUnsignedShort(const unsigned short v) {
	writeShort((short) v);
}

void RandomAccessInternalEeprom::writeInt(const int v) {
	writeBytes((unsigned char *) &v, sizeof(int));
}

void RandomAccessInternalEeprom::writeUnsignedInt(const unsigned int v) {
	writeInt((int) v);
}

void RandomAccessInternalEeprom::writeLong(const long v) {
	writeBytes((unsigned char *) &v, sizeof(long));
}

void RandomAccessInternalEeprom::writeUnsignedLong(const unsigned long v) {
	writeLong((long) v);
}

void RandomAccessInternalEeprom::writeFloat(const float v) {
	writeLong((long) v);
}

void RandomAccessInternalEeprom::writeDouble(const double v) {
	writeLong((long) v);
}

unsigned char RandomAccessInternalEeprom::readByte() {
	return readUnsignedChar();
}

bool RandomAccessInternalEeprom::readBoolean() {
	return (bool) readUnsignedChar();
}

char RandomAccessInternalEeprom::readChar() {
	return (char) readUnsignedChar();
}

unsigned char RandomAccessInternalEeprom::readUnsignedChar() {
	unsigned char c = 0;
	readFully(&c, 1);
	return c;
}

short RandomAccessInternalEeprom::readShort() {
	short v = 0;
	readFully((unsigned char *) &v, sizeof(short));
	return v;
}

unsigned short RandomAccessInternalEeprom::readUnsignedShort() {
	return (unsigned short) readShort();
}

int RandomAccessInternalEeprom::readInt() {
	int v = 0;
	readFully((unsigned char *) &v, sizeof(int));
	return v;
}

unsigned int RandomAccessInternalEeprom::readUnsignedInt() {
	return (unsigned int) readInt();
}

long RandomAccessInternalEeprom::readLong() {
	long v = 0;
	readFully((unsigned char *) &v, sizeof(long));
	return v;
}

unsigned long RandomAccessInternalEeprom::readUnsignedLong() {
	return (unsigned long) readLong();
}

float RandomAccessInternalEeprom::readFloat() {
	return (float) readLong();
}

double RandomAccessInternalEeprom::readDouble() {
	return (double) readLong();
}

void RandomAccessInternalEeprom::readFully(unsigned char *b, int len) {
	if (pos + len >= endPos) {
		len = endPos - pos;
	}
#ifdef ESP32
	EEPROM.readBytes(pos, (void *) b, len);
	pos += len;
#else
	for (int i = 0; i < len; i++) {
		b[i] = EEPROM.read(pos++);
	}
#endif
}

unsigned int RandomAccessInternalEeprom::skip(unsigned int n) {
	if (pos + n >= endPos) {
		n = endPos - pos;
	}
	pos += n;
	return n;
}

#endif// OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED
