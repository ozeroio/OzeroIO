#if OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "InternalEepromInputStream.h"
#include <EEPROM.h>
#include <io.h>

typedef void *pVoid;
InternalEepromInputStream::InternalEepromInputStream() : pos(0),
														 markPos(0),
														 eepromSize(EEPROM.length()) {
}

int InternalEepromInputStream::available() {
	return eepromSize - pos;
}

void InternalEepromInputStream::mark() {
	markPos = pos;
}

bool InternalEepromInputStream::markSupported() {
	return true;
}

int InternalEepromInputStream::read() {
	if (pos >= eepromSize) {
		return -1;
	}
	return (int) EEPROM.read(pos++);
}

int InternalEepromInputStream::read(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return 0;
	}
	const int n = ozero_min(eepromSize - pos, len);
#ifdef ESP32
	int readBytes = (int) EEPROM.readBytes(pos, &b[off], n);
	pos += readBytes;
	return readBytes;
#else
	for (int i = 0; i < n; i++) {
		b[off + i] = EEPROM.read((int) pos++);
	}
	return n;
#endif
}

void InternalEepromInputStream::reset() {
	pos = markPos;
}

void InternalEepromInputStream::seek(int pos) {
	if (pos < eepromSize) {
		this->pos = pos;
	}
}

#endif// OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED
