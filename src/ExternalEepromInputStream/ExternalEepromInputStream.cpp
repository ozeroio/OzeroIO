#if OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "ExternalEepromInputStream.h"
#include <limits.h>

ExternalEepromInputStream::ExternalEepromInputStream(ExternalEeprom *externalEeprom) : externalEeprom(externalEeprom),
																					   pos(0),
																					   markPos(0) {

	auto size = externalEeprom->getDeviceSize();

	// Int is used to address the stream, so lets make sure we don't overflow in any 16bit int archs.
	externalEepromSize = (size > INT_MAX) ? INT_MAX : (int) size;
}

int ExternalEepromInputStream::available() {
	return externalEepromSize - pos;
}

int ExternalEepromInputStream::read() {
	if (pos >= externalEepromSize) {
		return -1;
	}
	return (int) externalEeprom->read(pos++);
}

int ExternalEepromInputStream::read(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return 0;
	}
	const int available = (externalEepromSize - pos);
	if (available == 0) {
		return -1;
	}
	const int readBytes = (int) externalEeprom->readBytes(pos, &b[off], ozero_min(len, available));
	pos += readBytes;
	return readBytes;
}

void ExternalEepromInputStream::mark() {
	markPos = pos;
}

bool ExternalEepromInputStream::markSupported() {
	return true;
}

void ExternalEepromInputStream::reset() {
	pos = markPos;
}

void ExternalEepromInputStream::seek(const int pos) {
	this->pos = ozero_min(pos, externalEepromSize - 1);
}

#endif// OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED