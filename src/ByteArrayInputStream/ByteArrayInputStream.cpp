#include "ByteArrayInputStream.h"

ByteArrayInputStream::ByteArrayInputStream(unsigned char* buf,
        unsigned int count) :
        buf(buf), count(count) {
    markpos = 0;
    pos = 0;
}

int ByteArrayInputStream::available() {
    if ((count - pos) > 0) {
        return 1;
    }
    return 0;
}

void ByteArrayInputStream::mark() {
    markpos = pos;
}

bool ByteArrayInputStream::markSupported() {
    return true;
}

int ByteArrayInputStream::read() {
    if (pos >= count) {
        return -1;
    }
    return buf[pos++];
}

void ByteArrayInputStream::reset() {
    pos = markpos;
}

void ByteArrayInputStream::seek(unsigned int pos) {
    if (pos < count) {
        this->pos = pos;
    }
}