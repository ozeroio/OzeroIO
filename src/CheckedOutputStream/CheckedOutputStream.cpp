/**
 * An output stream that also maintains a checksum of the data being
 * written. The checksum can then be used to verify the integrity of
 * the output data.
 */

#include "CheckedOutputStream.h"

CheckedOutputStream::CheckedOutputStream(OutputStream *outputStream, Checksum *checksum) : FilterOutputStream(outputStream), checksum(checksum) {
}

Checksum *CheckedOutputStream::getChecksum() {
	return checksum;
}

void CheckedOutputStream::write(unsigned char b) {
	checksum->update(b);
	outputStream->write(b);
}

void CheckedOutputStream::write(unsigned char *b, int len) {
	write(b, 0, len);
}

void CheckedOutputStream::write(unsigned char *b, int off, int len) {
	checksum->update(b, off, len);
	outputStream->write(b, off, len);
}
