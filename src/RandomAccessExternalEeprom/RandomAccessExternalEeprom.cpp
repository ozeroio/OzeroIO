#if OZERO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "RandomAccessExternalEeprom.h"
#include <ExternalEeprom/ExternalEeprom.h>
#include <climits>

RandomAccessExternalEeprom::RandomAccessExternalEeprom(ExternalEeprom *externalEeprom) : externalEeprom(externalEeprom),
																						 pos(0) {
	auto deviceSize = externalEeprom->getDeviceSize();
	size = (deviceSize > INT_MAX) ? INT_MAX : (int) deviceSize;
}

int RandomAccessExternalEeprom::length() const {
	return size;
}

void RandomAccessExternalEeprom::seek(const int pos) {
	if (pos < size) {
		this->pos = pos;
	}
}

void RandomAccessExternalEeprom::close() {
}

void RandomAccessExternalEeprom::write(const unsigned char b) {
	if (pos < size) {
		externalEeprom->write(pos++, b);
	}
}

void RandomAccessExternalEeprom::write(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return;
	}
	const int n = ozero_min(len, size - pos);

	// Use offset for writing bytes to external EEPROM.
	const int writtenBytes = (int) externalEeprom->writeBytes(pos, &b[off], n);
	pos += writtenBytes;
}

int RandomAccessExternalEeprom::read() {
	if (pos >= size) {
		return -1;
	}
	return (int) externalEeprom->read(pos++);
}

int RandomAccessExternalEeprom::read(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return 0;
	}
	if (pos >= size) {
		return -1;
	}
	const int n = ozero_min(len, size - pos);
	// Use offset for reading bytes from external EEPROM.
	const int readBytes = (int) externalEeprom->readBytes(pos, &b[off], n);
	pos += readBytes;
	return readBytes;
}

int RandomAccessExternalEeprom::skip(const int n) {
	int newPos = pos + n;
	if (newPos > size) {
		newPos = size;
	}
	const int skipped = newPos - pos;
	pos = newPos;
	return skipped;
}

#endif// OZERO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED
