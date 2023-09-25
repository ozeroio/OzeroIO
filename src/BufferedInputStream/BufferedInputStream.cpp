#include "BufferedInputStream.h"
#include <InputStream/InputStream.h>
#include <limits.h>
#include <string.h>

BufferedInputStream::BufferedInputStream(InputStream *inputStream, unsigned char *buf, const int size)
	: FilterInputStream(inputStream),
	  size(size),
	  buf(buf),
	  head(0),
	  pos(0),
	  marked(false),
	  markPos(0) {
}

int BufferedInputStream::available() {
	const int underliningAvailable = inputStream->available();
	const int available = head - pos;

	// Both available might overflow the singed int.
	return available > (INT_MAX - underliningAvailable) ? INT_MAX : underliningAvailable + available;
}

void BufferedInputStream::close() {
	inputStream->close();
}

void BufferedInputStream::reset() {
	if (marked) {
		pos = markPos;
	}
}

int BufferedInputStream::read(unsigned char *b, const int len) {
	return read(b, 0, len);
}

int BufferedInputStream::read(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return 0;
	}
	int n = 0;
	for (;;) {
		const int p = readPortion(b, off + n, len - n);

		// In case we couldn't read anything.
		if (p <= 0) {

			// If nothing was read so far, return the result from readPortion (potentially -1)
			// Otherwise, return n.
			return (n == 0) ? p : n;
		}

		n += p;

		// In case we've done reading.
		if (n >= len) {
			return n;
		}

		// In case the underlying input stream doesn't have more available data.
		if (inputStream->available() <= 0) {
			return n;
		}
	}
}

int BufferedInputStream::read() {

	const int available = head - pos;

	// If buffer is empty.
	if (available <= 0) {
		fillBuffer();

		// We just attempted to fill the buffer, but nothing was fetched.
		if (head - pos <= 0) {
			return -1;
		}
	}
	return (int) buf[pos++];
}

void BufferedInputStream::shiftBuffer() {
	if (pos > 0) {
		marked = false;
		const int available = head - pos;
		for (int i = 0; i < available; i++) {
			buf[i] = buf[pos + i];
		}
		head -= pos;
		pos = 0;
	}
}

void BufferedInputStream::fillBuffer() {
	shiftBuffer();
	const int space = size - head;
	const int n = inputStream->read(buf, pos, space);
	head = n;
}

void BufferedInputStream::mark() {
	fillBuffer();
	markPos = 0;
	marked = true;
}

bool BufferedInputStream::markSupported() {
	return true;
}

int BufferedInputStream::skip(const int n) {
	const int available = head - pos;

	// In case we can skip within the buffer.
	if (available >= n) {
		pos += n;
		return n;
	}
	pos = 0;
	head = 0;
	marked = false;
	const int skipped = available + inputStream->skip(n - available);
	return skipped;
}

int BufferedInputStream::readPortion(unsigned char *b, const int off, const int len) {
	int available = head - pos;
	if (available <= 0) {

		// If the requested length is at least as large as the buffer,
		// do not bother to copy the bytes into the local buffer.
		if (len >= size) {
			return inputStream->read(b, off, len);
		}

		// None available, but the buffer size if bigger than required len.
		// Fill the buffer, then.
		fillBuffer();
		available = head - pos;

		// We just attempted to fill the buffer, but nothing was fetched.
		if (available <= 0) {
			return -1;
		}
	}

	// Available > 0, lets read what is in the buffer.
	const int n = (available < len) ? available : len;

	// Poor into the input *needed* data from buffer.
	memcpy(&b[off], &buf[pos], n);
	pos += n;
	return n;
}
