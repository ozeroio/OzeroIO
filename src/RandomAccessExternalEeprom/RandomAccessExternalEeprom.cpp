#if __OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED__ == 1

#include <ExternalEeprom/ExternalEeprom.h>
#include "RandomAccessExternalEeprom.h"

RandomAccessExternalEeprom::RandomAccessExternalEeprom(ExternalEeprom* externalEeprom)
        : externalEeprom(externalEeprom) {
    pos = 0;
}

unsigned int RandomAccessExternalEeprom::length() {
    return (unsigned int) externalEeprom->getDeviceSize();
}

void RandomAccessExternalEeprom::seek(unsigned int pos) {
    this->pos = pos;
}

void RandomAccessExternalEeprom::close() {
}

void RandomAccessExternalEeprom::write(unsigned char* b, int len) {
    writeBytes(b, len);
}

void RandomAccessExternalEeprom::write(unsigned char b) {
    writeByte(b);
}

void RandomAccessExternalEeprom::writeByte(unsigned char b) {
    externalEeprom->write(pos++, b);
}

void RandomAccessExternalEeprom::writeBytes(unsigned char* b, int len) {
    for (int i = 0; i < len; i++) {
        externalEeprom->write(pos++, b[i]);
    }
}

void RandomAccessExternalEeprom::writeBoolean(bool v) {
    externalEeprom->write(pos++, (unsigned char) v);
}

void RandomAccessExternalEeprom::writeChar(char c) {
    externalEeprom->write(pos++, (unsigned char) c);
}

void RandomAccessExternalEeprom::writeUnsignedChar(unsigned char c) {
    externalEeprom->write(pos++, (unsigned char) c);
}

void RandomAccessExternalEeprom::writeInt(int v) {
    writeBytes((unsigned char *) &v, sizeof(int));
}

void RandomAccessExternalEeprom::writeUnsignedInt(unsigned int v) {
    writeInt((int) v);
}

void RandomAccessExternalEeprom::writeWord(word v) {
    writeInt((int) v);
}

void RandomAccessExternalEeprom::writeLong(long v) {
    writeBytes((unsigned char *) &v, sizeof(long));
}

void RandomAccessExternalEeprom::writeUnsignedLong(unsigned long v) {
    writeLong((long) v);
}

void RandomAccessExternalEeprom::writeFloat(float v) {
    writeLong((long) v);
}

void RandomAccessExternalEeprom::writeDouble(double v) {
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

int RandomAccessExternalEeprom::readInt() {
    int v = 0;
    readFully((unsigned char*) &v, sizeof(int));
    return v;
}

unsigned int RandomAccessExternalEeprom::readUnsignedInt() {
    return (unsigned int) readInt();
}

word RandomAccessExternalEeprom::readWord() {
    return (word) readInt();
}

long RandomAccessExternalEeprom::readLong() {
    long v = 0;
    readFully((unsigned char*) &v, sizeof(long));
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

void RandomAccessExternalEeprom::readFully(unsigned char* b, int len) {
    int avalilable = length() - pos;
    if (len > avalilable) {
        len = avalilable;
    }
    externalEeprom->readBytes(pos, b, len);
    pos += len;
}

unsigned int RandomAccessExternalEeprom::skipBytes(unsigned int n) {
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

#endif /* __OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED__ */
