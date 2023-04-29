#include "ByteArrayInputStream.h"
#include <limits.h>

ByteArrayInputStream::ByteArrayInputStream(unsigned char *buf, unsigned int count) : buf(buf), count(count) {
    markpos = 0;
    pos = 0;
}

int ByteArrayInputStream::available() {
    if (count >= pos) {
        const unsigned int diff = count - pos;
        if (diff > INT_MAX) {
            return INT_MAX;
        }
        return (int) diff;
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

void ByteArrayInputStream::seek(const unsigned int pos) {
    if (pos < count) {
        this->pos = pos;
    }
}