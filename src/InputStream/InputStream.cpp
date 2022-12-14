#include "InputStream.h"

int InputStream::available() {
    return 0;
}

void InputStream::close() {
}

void InputStream::mark() {
}

bool InputStream::markSupported() {
    return false;
}

int InputStream::read(unsigned char* b, int len) {
    return read(b, 0, len);
}

int InputStream::read(unsigned char* b, int off, int len) {
    int i, c;
    if (b == (unsigned char*) 0) {
        return 0;
    }
    c = read();
    if (c == -1) {
        return -1;
    }
    b[off] = (unsigned char) c;
    for (i = 1; i < len; i++) {
        c = read();
        if (c == -1) {
            break;
        }
        b[off + i] = (unsigned char) c;
    }
    return i;
}

void InputStream::reset() {
}

unsigned int InputStream::skip(unsigned int n) {
    unsigned int i;
    for (i = 0; i < n && available() > 0; i++) {
        read();
    }
    return i;
}