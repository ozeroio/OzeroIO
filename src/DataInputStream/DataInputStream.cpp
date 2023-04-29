#include "DataInputStream.h"

DataInputStream::DataInputStream(InputStream* inputStream) :
        inputStream(inputStream) {
}

unsigned char DataInputStream::readByte() {
    return (unsigned char) inputStream->read();
}

bool DataInputStream::readBoolean() {
    return (bool) inputStream->read();
}

char DataInputStream::readChar() {
    return (char) inputStream->read();
}

unsigned char DataInputStream::readUnsignedChar() {
    return (unsigned char) inputStream->read();
}

int DataInputStream::readInt() {
    int v = 0;
    readFully((unsigned char *) &v, sizeof(int));
    return v;
}

unsigned int DataInputStream::readUnsignedInt() {
    return (unsigned int) readInt();
}

long DataInputStream::readLong() {
    long v = 0;
    readFully((unsigned char *) &v, sizeof(long));
    return v;
}

unsigned long DataInputStream::readUnsignedLong() {
    return (unsigned long) readLong();
}

float DataInputStream::readFloat() {
    float v = 0;
    readFully((unsigned char *) &v, sizeof(float));
    return v;
}

double DataInputStream::readDouble() {
    return (double) readLong();
}

void DataInputStream::readFully(unsigned char *b, const int len) {
    for (int i = 0; i < len; i++) {
        b[i] = inputStream->read();
    }
}

unsigned int DataInputStream::skipBytes(const unsigned int n) {
    return inputStream->skip(n);
}