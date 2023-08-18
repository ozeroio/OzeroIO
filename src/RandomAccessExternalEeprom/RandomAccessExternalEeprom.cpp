#if OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "RandomAccessExternalEeprom.h"
#include <ExternalEeprom/ExternalEeprom.h>

RandomAccessExternalEeprom::RandomAccessExternalEeprom(ExternalEeprom *externalEeprom)
	: externalEeprom(externalEeprom) {
	pos = 0;
}

unsigned int RandomAccessExternalEeprom::length() {
	return (unsigned int) externalEeprom->getDeviceSize();
}

void RandomAccessExternalEeprom::seek(const unsigned int pos) {
	this->pos = pos;
}

void RandomAccessExternalEeprom::close() {
}

void RandomAccessExternalEeprom::write(unsigned char *b, const int len) {
	writeBytes(b, len);
}

void RandomAccessExternalEeprom::write(const unsigned char b) {
	writeByte(b);
}

void RandomAccessExternalEeprom::writeByte(const unsigned char b) {
	externalEeprom->write(pos++, b);
}

void RandomAccessExternalEeprom::writeBytes(unsigned char *b, const int len) {
	for (int i = 0; i < len; i++) {
		externalEeprom->write(pos++, b[i]);
	}
}

void RandomAccessExternalEeprom::writeBoolean(const bool v) {
	externalEeprom->write(pos++, (unsigned char) v);
}

void RandomAccessExternalEeprom::writeChar(const char c) {
	externalEeprom->write(pos++, (unsigned char) c);
}

void RandomAccessExternalEeprom::writeUnsignedChar(const unsigned char c) {
	externalEeprom->write(pos++, (unsigned char) c);
}

void RandomAccessExternalEeprom::writeShort(const short v) {
	writeBytes((unsigned char *) &v, sizeof(short));
}

void RandomAccessExternalEeprom::writeUnsignedShort(const unsigned short v) {
	writeShort((short) v);
}

void RandomAccessExternalEeprom::writeInt(const int v) {
	writeBytes((unsigned char *) &v, sizeof(int));
}

void RandomAccessExternalEeprom::writeUnsignedInt(const unsigned int v) {
	writeInt((int) v);
}

void RandomAccessExternalEeprom::writeLong(const long v) {
	writeBytes((unsigned char *) &v, sizeof(long));
}

void RandomAccessExternalEeprom::writeUnsignedLong(const unsigned long v) {
	writeLong((long) v);
}

void RandomAccessExternalEeprom::writeFloat(const float v) {
	writeLong((long) v);
}

void RandomAccessExternalEeprom::writeDouble(const double v) {
	writeLong((long) v);
}

unsigned char RandomAccessExternalEeprom::readByte() {
	return (unsigned char) externalEeprom->read(pos++);
}

bool RandomAccessExternalEeprom::readBoolean() {
	return (bool) externalEeprom->read(pos++);
}

char RandomAccessExternalEeprom::readChar() {
	return (char) externalEeprom->read(pos++);
}

unsigned char RandomAccessExternalEeprom::readUnsignedChar() {
	return (unsigned char) externalEeprom->read(pos++);
}

short RandomAccessExternalEeprom::readShort() {
	int v = 0;
	readFully((unsigned char *) &v, sizeof(short));
	return v;
}

unsigned short RandomAccessExternalEeprom::readUnsignedShort() {
	return (unsigned short) readShort();
}

int RandomAccessExternalEeprom::readInt() {
	int v = 0;
	readFully((unsigned char *) &v, sizeof(int));
	return v;
}

unsigned int RandomAccessExternalEeprom::readUnsignedInt() {
	return (unsigned int) readInt();
}

long RandomAccessExternalEeprom::readLong() {
	long v = 0;
	readFully((unsigned char *) &v, sizeof(long));
	return v;
}

unsigned long RandomAccessExternalEeprom::readUnsignedLong() {
	return (unsigned long) readLong();
}

float RandomAccessExternalEeprom::readFloat() {
	return (float) readLong();
}

double RandomAccessExternalEeprom::readDouble() {
	return (double) readLong();
}

void RandomAccessExternalEeprom::readFully(unsigned char *b, int len) {
	int available = length() - pos;
	len = ozero_min(available, len);
	externalEeprom->readBytes(pos, b, len);
	pos += len;
}

unsigned int RandomAccessExternalEeprom::skipBytes(const unsigned int n) {
	unsigned int skipped;
	unsigned int newpos;
	newpos = pos + n;
	if (newpos > length()) {
		newpos = length();
	}
	skipped = newpos - pos;
	pos = newpos;
	return skipped;
}

#endif// OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED
