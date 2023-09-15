#include "FilterOutputStream.h"

FilterOutputStream::FilterOutputStream(OutputStream *outputStream) : outputStream(outputStream) {
}

void FilterOutputStream::write(unsigned char b) {
	outputStream->write(b);
}

void FilterOutputStream::write(unsigned char *b, int len) {
	outputStream->write(b, len);
}

void FilterOutputStream::write(unsigned char *b, int off, int len) {
	outputStream->write(b, off, len);
}

void FilterOutputStream::flush() {
	outputStream->flush();
}

void FilterOutputStream::close() {
	outputStream->flush();
	outputStream->close();
}
