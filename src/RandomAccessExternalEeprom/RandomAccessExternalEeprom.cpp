#if OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "RandomAccessExternalEeprom.h"
#include <ExternalEeprom/ExternalEeprom.h>

RandomAccessExternalEeprom::RandomAccessExternalEeprom(ExternalEeprom *externalEeprom) : externalEeprom(externalEeprom),
																						 size(externalEeprom->getDeviceSize()),
																						 pos(0) {
}

unsigned int RandomAccessExternalEeprom::length() const {
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
	const int writtenBytes = externalEeprom->writeBytes(pos, b, n);
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
	const int readBytes = externalEeprom->readBytes(pos, b, n);
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

#endif// OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED
