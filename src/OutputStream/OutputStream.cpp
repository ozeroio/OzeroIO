#include "OutputStream.h"

void OutputStream::write(unsigned char* b, int len) {
    write(b, 0, len);
}

void OutputStream::write(unsigned char* b, int off, int len) {
    if (b == nullptr || len == 0) {
        return;
    }
    for (int i = 0; i < len; i++) {
        write(b[off + i]);
    }
}

void OutputStream::flush() {
}

void OutputStream::close() {
}

void OutputStream::mark() {
}

bool OutputStream::markSupported() {
    return false;
}

void OutputStream::reset() {
}
