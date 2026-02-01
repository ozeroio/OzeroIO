/**
 * A <code>CheckedInputStream</code> contains
 * some other input stream, which it uses as
 * its  basic source of data, possibly transforming
 * the data along the way or providing  additional
 * functionality. The class <code>CheckedInputStream</code>
 * itself simply overrides all  methods of
 * <code>InputStream</code> with versions that
 * pass all requests to the contained  input
 * stream. Subclasses of <code>CheckedInputStream</code>
 * may further override some of  these methods
 * and may also provide additional methods
 * and fields.
 */

#include "CheckedInputStream.h"

CheckedInputStream::CheckedInputStream(InputStream *inputStream, Checksum *checksum) : FilterInputStream(inputStream), checksum(checksum) {
}

Checksum *CheckedInputStream::getChecksum() {
	return checksum;
}

int CheckedInputStream::read() {
	int b = inputStream->read();
	if (b != -1) {
		checksum->update(b);
	}
	return b;
}

int CheckedInputStream::read(unsigned char *b, int len) {
	return read(b, 0, len);
}

int CheckedInputStream::read(unsigned char *b, int off, int len) {
	len = inputStream->read(b, off, len);
	if (len != -1) {
		checksum->update(b, off, len);
	}
	return len;
}