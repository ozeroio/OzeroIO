#include "FilterOutputStream.h"

FilterOutputStream::FilterOutputStream(OutputStream *out) : out(out) {
}

void FilterOutputStream::write(unsigned char b) {
	out->write(b);
}

void FilterOutputStream::write(unsigned char *b, int len) {
	out->write(b, len);
}

void FilterOutputStream::write(unsigned char *b, int off, int len) {
	out->write(b, off, len);
}

void FilterOutputStream::flush() {
	out->flush();
}

void FilterOutputStream::close() {
	out->flush();
	out->close();
}
