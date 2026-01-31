#include "InputStream.h"

int InputStream::available() {
	return 0;
}

void InputStream::close() {
}

void InputStream::mark() {
}

bool InputStream::markSupported() {

	// By default, input streams don't support mark.
	return false;
}

bool InputStream::isMarked() {
	return false;
}

int InputStream::read(unsigned char *b, const int len) {
	return read(b, 0, len);
}

int InputStream::read(unsigned char *b, int off, const int len) {
	if (b == nullptr) {
		return 0;
	}
	int c = read();
	if (c == -1) {
		return -1;
	}
	b[off] = (unsigned char) c;
	int i;
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

int InputStream::skip(int n) {
	int i;

	// Dummy way to skip the stream.
	// Derived streams should implement their own (optimized) ways to skip.
	for (i = 0; i < n && available() > 0; i++) {
		read();
	}
	return i;
}