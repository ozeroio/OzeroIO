#include "ByteArrayOutputStream.h"
#include <cstring>
#include <io.h>

ByteArrayOutputStream::ByteArrayOutputStream(unsigned char *buf, const int size)
	: buf(buf), size(size), pos(0), markPos(0) {
}

int ByteArrayOutputStream::getBufferSize() const {
	return size;
}

unsigned char *ByteArrayOutputStream::getBuffer() {
	return buf;
}

void ByteArrayOutputStream::write(const unsigned char b) {
	if (pos < size) {
		buf[pos++] = b;
	}
}

void ByteArrayOutputStream::write(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return;
	}
	const int n = ozero_min(len, size - pos);
	memcpy(&buf[pos], &b[off], n);
	pos += n;
}

void ByteArrayOutputStream::mark() {
	markPos = pos;
}

bool ByteArrayOutputStream::markSupported() {
	return true;
}

void ByteArrayOutputStream::reset() {
	pos = markPos;
}

void ByteArrayOutputStream::seek(const int pos) {
	if (pos < size) {
		this->pos = pos;
	}
}
