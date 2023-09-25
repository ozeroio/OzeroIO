#include "DataInput.h"

int DataInput::read(unsigned char *b, int len) {
	return read(b, 0, len);
}

unsigned char DataInput::readByte() {
	return (unsigned char) read();
}

bool DataInput::readBoolean() {
	return (bool) read();
}

char DataInput::readChar() {
	return (char) read();
}

unsigned char DataInput::readUnsignedChar() {
	return (unsigned char) read();
}

short DataInput::readShort() {
	short v = 0;
	read((unsigned char *) &v, sizeof(short));
	return v;
}

unsigned short DataInput::readUnsignedShort() {
	return (unsigned short) readShort();
}

int DataInput::readInt() {
	int v = 0;
	read((unsigned char *) &v, sizeof(int));
	return v;
}

unsigned int DataInput::readUnsignedInt() {
	return (unsigned int) readInt();
}

long DataInput::readLong() {
	long v = 0;
	read((unsigned char *) &v, sizeof(long));
	return v;
}

unsigned long DataInput::readUnsignedLong() {
	return (unsigned long) readLong();
}

float DataInput::readFloat() {
	float v = 0;
	read((unsigned char *) &v, sizeof(float));
	return v;
}

double DataInput::readDouble() {
	double v = 0;
	read((unsigned char *) &v, sizeof(double));
	return v;
}
