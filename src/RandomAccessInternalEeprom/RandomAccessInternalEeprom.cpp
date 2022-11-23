#if __OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED__ == 1

#include "RandomAccessInternalEeprom.h"
#include <EEPROM.h>

RandomAccessInternalEeprom::RandomAccessInternalEeprom(unsigned int startPos, unsigned int endPos) : pos(startPos), startPos(startPos), endPos(endPos) {
}

unsigned int RandomAccessInternalEeprom::length() {
    return (unsigned int) endPos - startPos;
}

void RandomAccessInternalEeprom::seek(unsigned int pos) {
    if (pos >= length()) {
        pos = length() - 1;
    }
    this->pos = startPos + pos;
}

void RandomAccessInternalEeprom::close() {
}

void RandomAccessInternalEeprom::write(unsigned char* b, int len) {
    writeBytes(b, len);
}

void RandomAccessInternalEeprom::write(unsigned char b) {
    writeByte(b);
}

void RandomAccessInternalEeprom::writeByte(unsigned char b) {
    writeBytes((unsigned char*)&b, 1);
}

void RandomAccessInternalEeprom::writeBytes(unsigned char* b, int len) {
    if (pos + len >= endPos) {
        len = endPos - pos;
    }
    int written = EEPROM.writeBytes(pos, (void *) b, len);
    EEPROM.commit();
    pos += written;
}

void RandomAccessInternalEeprom::writeBoolean(bool v) {
    writeBytes((unsigned char*)&v, 1);
}

void RandomAccessInternalEeprom::writeChar(char c) {
    writeBytes((unsigned char*)&c, 1);
}

void RandomAccessInternalEeprom::writeUnsignedChar(unsigned char c) {
    writeBytes((unsigned char*)&c, 1);
}

void RandomAccessInternalEeprom::writeInt(int v) {
    writeBytes((unsigned char*)&v, sizeof(int));
}

void RandomAccessInternalEeprom::writeUnsignedInt(unsigned int v) {
    writeInt((int) v);
}

void RandomAccessInternalEeprom::writeLong(long v) {
    writeBytes((unsigned char*)&v, sizeof(long));
}

void RandomAccessInternalEeprom::writeUnsignedLong(unsigned long v) {
    writeLong((long) v);
}

void RandomAccessInternalEeprom::writeFloat(float v) {
    writeLong((long) v);
}

void RandomAccessInternalEeprom::writeDouble(double v) {
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

int RandomAccessInternalEeprom::readInt() {
    int v = 0;
    readFully((unsigned char*)&v, sizeof(int));
    return v;
}

unsigned int RandomAccessInternalEeprom::readUnsignedInt() {
    return (unsigned int) readInt();
}

long RandomAccessInternalEeprom::readLong() {
    long v = 0;
    readFully((unsigned char*)&v, sizeof(long));
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

void RandomAccessInternalEeprom::readFully(unsigned char* b, int len) {
    if (pos + len >= endPos) {
        len = endPos - pos;
    }
    EEPROM.readBytes(pos, (void *) b, len);
    pos += len;
}

unsigned int RandomAccessInternalEeprom::skipBytes(unsigned int n) {
    if (pos + n >= endPos) {
        n = endPos - pos;
    }
    pos += n;
    return n;
}

#endif /* __OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED__ */

