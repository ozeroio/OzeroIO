#include "FilterInputStream.h"

FilterInputStream::FilterInputStream(InputStream *inputStream) : inputStream(inputStream) {
}

int FilterInputStream::read() {
	return inputStream->read();
}

int FilterInputStream::read(unsigned char *b, int len) {
	return inputStream->read(b, len);
}

int FilterInputStream::read(unsigned char *b, int off, int len) {
	return inputStream->read(b, off, len);
}

unsigned int FilterInputStream::skip(unsigned int n) {
	return inputStream->skip(n);
}

int FilterInputStream::available() {
	return inputStream->available();
}

void FilterInputStream::close() {
	inputStream->close();
}

void FilterInputStream::mark() {
	inputStream->mark();
}

void FilterInputStream::reset() {
	inputStream->reset();
}

bool FilterInputStream::markSupported() {
	return inputStream->markSupported();
}
