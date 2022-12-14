#include "BufferedOutputStream.h"

BufferedOutputStream::BufferedOutputStream(OutputStream* out, unsigned char* buf, int size)
        : FilterOutputStream(out), buf(buf), size(size), count(0) {
}

void BufferedOutputStream::write(unsigned char b) {
    if (count >= size) {
        flushBuffer();
    }
    buf[count++] = b;
}

void BufferedOutputStream::write(unsigned char* b, int len) {
    write(b, 0, len);
}

void BufferedOutputStream::write(unsigned char* b, int off, int len) {

    /*
     * If the request length exceeds the size of the output buffer,
     * flush the output buffer and then write the data directly.
     * In this way buffered streams will cascade harmlessly. 
     */
    if (len >= size) {
        flushBuffer();
        out->write(b, off, len);
        return;
    }
    if (len > size - count) {
        flushBuffer();
    }
    for (int i = 0; i < len; i++) {
        buf[count + i] = b[off + i];
    }
    count += len;
}

void BufferedOutputStream::flush() {
    flushBuffer();
    out->flush();
}

void BufferedOutputStream::close() {
    flush();
    out->close();
}

void BufferedOutputStream::flushBuffer() {
    if (count > 0) {
        out->write(buf, 0, count);
        count = 0;
    }
}
