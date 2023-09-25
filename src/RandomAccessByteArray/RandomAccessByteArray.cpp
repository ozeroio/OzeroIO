#include "RandomAccessByteArray.h"
#include <io.h>
#include <string.h>

RandomAccessByteArray::RandomAccessByteArray(unsigned char *buf,
											 const int size) : buf(buf),
															   size(size),
															   pos(0) {
}

unsigned int RandomAccessByteArray::length() const {
	return size;
}

void RandomAccessByteArray::seek(const int pos) {
	if (pos < size) {
		this->pos = pos;
	}
}

void RandomAccessByteArray::close() {
}

void RandomAccessByteArray::write(const unsigned char b) {
	if (pos < size) {
		buf[pos++] = b;
	}
}

void RandomAccessByteArray::write(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return;
	}
	const int n = ozero_min(size - pos, len);
	memcpy(&buf[pos], &b[off], n);
	pos += n;
}

int RandomAccessByteArray::read() {
	if (pos >= size) {
		return -1;
	}
	return (int) buf[pos++];
}

int RandomAccessByteArray::read(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return 0;
	}
	if (pos >= size) {
		return -1;
	}
	const int n = ozero_min(len, size - pos);
	memcpy(&b[off], &buf[pos], n);
	pos += n;
	return n;
}

int RandomAccessByteArray::skip(const int n) {
	int newPos = pos + n;
	if (newPos > size) {
		newPos = size;
	}
	const int skipped = newPos - pos;
	pos = newPos;
	return skipped;
}
