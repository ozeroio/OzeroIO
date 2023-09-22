#include "ByteArrayInputStream.h"
#include <io.h>
#include <string.h>

ByteArrayInputStream::ByteArrayInputStream(unsigned char *buf, const int size) : buf(buf),
																				 size(size) {
	markPos = 0;
	pos = 0;
}

int ByteArrayInputStream::available() {
	return size - pos;
}

void ByteArrayInputStream::mark() {
	markPos = pos;
}

bool ByteArrayInputStream::markSupported() {
	return true;
}

int ByteArrayInputStream::read() {
	if (pos >= size) {
		return -1;
	}
	return (int) buf[pos++];
}

int ByteArrayInputStream::read(unsigned char *b, const int off, const int len) {
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


void ByteArrayInputStream::reset() {
	pos = markPos;
}

void ByteArrayInputStream::seek(const int pos) {
	if (pos < size) {
		this->pos = pos;
	}
}