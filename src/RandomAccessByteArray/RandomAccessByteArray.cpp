#include "RandomAccessByteArray.h"

RandomAccessByteArray::RandomAccessByteArray(unsigned char *buf,
											 unsigned int count) : buf(buf), count(count) {
	pos = 0;
}

unsigned int RandomAccessByteArray::length() const {
	return count;
}

void RandomAccessByteArray::seek(const unsigned int pos) {
	this->pos = pos;
}

void RandomAccessByteArray::close() {
}

void RandomAccessByteArray::write(unsigned char *b, const int len) {
	writeBytes(b, len);
}

void RandomAccessByteArray::write(const unsigned char b) {
	buf[pos++] = b;
}

void RandomAccessByteArray::writeByte(const unsigned char b) {
	buf[pos++] = b;
}

void RandomAccessByteArray::writeBytes(unsigned char *b, const int len) {
	for (int i = 0; i < len; i++) {
		buf[pos++] = b[i];
	}
}

void RandomAccessByteArray::writeBoolean(const bool v) {
	buf[pos++] = (unsigned char) v;
}

void RandomAccessByteArray::writeChar(const char c) {
	buf[pos++] = (unsigned char) c;
}

void RandomAccessByteArray::writeUnsignedChar(const unsigned char c) {
	buf[pos++] = (unsigned char) c;
}

void RandomAccessByteArray::writeShort(const short v) {
	writeBytes((unsigned char *) &v, sizeof(short));
}

void RandomAccessByteArray::writeUnsignedShort(const unsigned short v) {
	writeShort((short) v);
}

void RandomAccessByteArray::writeInt(const int v) {
	writeBytes((unsigned char *) &v, sizeof(int));
}

void RandomAccessByteArray::writeUnsignedInt(const unsigned int v) {
	writeInt((int) v);
}

void RandomAccessByteArray::writeLong(const long v) {
	writeBytes((unsigned char *) &v, sizeof(long));
}

void RandomAccessByteArray::writeUnsignedLong(const unsigned long v) {
	writeLong((long) v);
}

void RandomAccessByteArray::writeFloat(const float v) {
	writeLong((long) v);
}

void RandomAccessByteArray::writeDouble(const double v) {
	writeLong((long) v);
}

unsigned char RandomAccessByteArray::readByte() {
	return buf[pos++];
}

bool RandomAccessByteArray::readBoolean() {
	return (bool) buf[pos++];
}

char RandomAccessByteArray::readChar() {
	return (char) buf[pos++];
}

unsigned char RandomAccessByteArray::readUnsignedChar() {
	return (unsigned char) buf[pos++];
}

short RandomAccessByteArray::readShort() {
	int v = 0;
	readFully((unsigned char *) &v, sizeof(short));
	return v;
}

unsigned short RandomAccessByteArray::readUnsignedShort() {
	return (unsigned short) readShort();
}

int RandomAccessByteArray::readInt() {
	int v = 0;
	readFully((unsigned char *) &v, sizeof(int));
	return v;
}

unsigned int RandomAccessByteArray::readUnsignedInt() {
	return (unsigned int) readInt();
}

long RandomAccessByteArray::readLong() {
	long v = 0;
	readFully((unsigned char *) &v, sizeof(long));
	return v;
}

unsigned long RandomAccessByteArray::readUnsignedLong() {
	return (unsigned long) readLong();
}

float RandomAccessByteArray::readFloat() {
	return (float) readLong();
}

double RandomAccessByteArray::readDouble() {
	return (double) readLong();
}

void RandomAccessByteArray::readFully(unsigned char *b, const int len) {
	for (int i = 0; i < len; i++) {
		b[i] = buf[pos++];
	}
}

unsigned int RandomAccessByteArray::skipBytes(const unsigned int n) {
	unsigned int skipped;
	unsigned int newpos;
	newpos = pos + n;
	if (newpos > count) {
		newpos = count;
	}
	skipped = newpos - pos;
	pos = newpos;
	return skipped;
}
