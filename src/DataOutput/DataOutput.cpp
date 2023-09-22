#include "DataOutput.h"

void DataOutput::write(unsigned char *b, const int len) {
	write(b, 0, len);
}

void DataOutput::writeByte(const unsigned char b) {
	write(b);
}

void DataOutput::writeBoolean(const bool v) {
	write((unsigned char) v);
}

void DataOutput::writeChar(const char c) {
	write((unsigned char) c);
}

void DataOutput::writeUnsignedChar(const unsigned char c) {
	write((unsigned char) c);
}

void DataOutput::writeShort(const short v) {
	write((unsigned char *) &v, sizeof(short));
}

void DataOutput::writeUnsignedShort(const unsigned short v) {
	writeShort((short) v);
}

void DataOutput::writeInt(const int v) {
	write((unsigned char *) &v, sizeof(int));
}

void DataOutput::writeUnsignedInt(const unsigned int v) {
	writeInt((int) v);
}

void DataOutput::writeLong(const long v) {
	write((unsigned char *) &v, sizeof(long));
}

void DataOutput::writeUnsignedLong(const unsigned long v) {
	writeLong((long) v);
}

void DataOutput::writeFloat(const float v) {
	write((unsigned char *) &v, sizeof(float));
}

void DataOutput::writeDouble(const double v) {
	write((unsigned char *) &v, sizeof(double));
}