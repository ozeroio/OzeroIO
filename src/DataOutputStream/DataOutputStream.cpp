#include "DataOutputStream.h"

DataOutputStream::DataOutputStream(OutputStream* outputStream) :
        outputStream(outputStream) {
}

void DataOutputStream::write(unsigned char *b, const int len) {
    writeBytes(b, len);
}

void DataOutputStream::write(const unsigned char b) {
    writeByte(b);
}

void DataOutputStream::writeByte(const unsigned char b) {
    outputStream->write(b);
}

void DataOutputStream::writeBytes(unsigned char *b, const int len) {
    for (int i = 0; i < len; i++) {
        outputStream->write(b[i]);
    }
}

void DataOutputStream::writeBoolean(const bool v) {
    outputStream->write((unsigned char) v);
}

void DataOutputStream::writeChar(const char c) {
    outputStream->write((unsigned char) c);
}

void DataOutputStream::writeUnsignedChar(const unsigned char c) {
    outputStream->write((unsigned char) c);
}

void DataOutputStream::writeInt(const int v) {
    writeBytes((unsigned char *) &v, sizeof(int));
}

void DataOutputStream::writeUnsignedInt(const unsigned int v) {
    writeInt((int) v);
}

void DataOutputStream::writeLong(const long v) {
    writeBytes((unsigned char *) &v, sizeof(long));
}

void DataOutputStream::writeUnsignedLong(const unsigned long v) {
    writeLong((long) v);
}

void DataOutputStream::writeFloat(const float v) {
    writeBytes((unsigned char *) &v, sizeof(float));
}

void DataOutputStream::writeDouble(const double v) {
    writeBytes((unsigned char *) &v, sizeof(double));
}