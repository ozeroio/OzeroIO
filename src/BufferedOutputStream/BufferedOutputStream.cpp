#include "BufferedOutputStream.h"
#include <string.h>

BufferedOutputStream::BufferedOutputStream(OutputStream *outputStream, unsigned char *buf, const int size)
	: FilterOutputStream(outputStream), buf(buf), size(size), pos(0) {
}

void BufferedOutputStream::write(const unsigned char b) {
	if (pos >= size) {
		flushBuffer();
	}
	buf[pos++] = b;
}

void BufferedOutputStream::write(unsigned char *b, const int len) {
	write(b, 0, len);
}

void BufferedOutputStream::write(unsigned char *b, const int off, const int len) {

	auto available = size - pos;

	if (len > available) {

		/*
		 * If the request length exceeds the size of the available space,
		 * flush the output buffer and then write the data directly.
		 */
		flushBuffer();
		outputStream->write(b, off, len);
	} else {

		/*
		 * The request length is smaller or equals than the remaining
		 * available space inside the buffer.
		 */
		memcpy(&buf[pos], &b[off], len);
		pos += len;
	}
}

void BufferedOutputStream::flush() {
	flushBuffer();
	outputStream->flush();
}

void BufferedOutputStream::close() {
	flush();
	outputStream->close();
}

void BufferedOutputStream::reset() {
	flush();
	outputStream->reset();
}

void BufferedOutputStream::flushBuffer() {
	if (pos > 0) {
		outputStream->write(buf, 0, pos);
		pos = 0;
	}
}