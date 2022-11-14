#include "FilterInputStream.h"

FilterInputStream::FilterInputStream(InputStream* in) :
        in(in) {
}

int FilterInputStream::read() {
    return in->read();
}

int FilterInputStream::read(unsigned char* b, int len) {
    return in->read(b, len);
}

int FilterInputStream::read(unsigned char* b, int off, int len) {
    return in->read(b, off, len);
}

unsigned int FilterInputStream::skip(unsigned int n) {
    return in->skip(n);
}

int FilterInputStream::available() {
    return in->available();
}

void FilterInputStream::close() {
    in->close();
}

void FilterInputStream::mark() {
    in->mark();
}

void FilterInputStream::reset() {
    in->reset();
}

bool FilterInputStream::markSupported() {
    return in->markSupported();
}
