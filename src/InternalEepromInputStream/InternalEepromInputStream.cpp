#if OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "InternalEepromInputStream.h"
#include <EEPROM.h>

InternalEepromInputStream::InternalEepromInputStream()
	: maxAvailableChunk(0x08), pos(0), markpos(0), eepromSize(EEPROM.length()) {
}

int InternalEepromInputStream::available() {
	int room = (int) (eepromSize - pos);
	if (room > maxAvailableChunk) {
		return maxAvailableChunk;
	}
	return room;
}

void InternalEepromInputStream::mark() {
	markpos = pos;
}

bool InternalEepromInputStream::markSupported() {
	return true;
}

int InternalEepromInputStream::read() {
	if (pos >= eepromSize) {
		return -1;
	}
	return (int) EEPROM.read((int) pos++);
}

int InternalEepromInputStream::read(unsigned char *b, int off, int len) {
	unsigned int available = (eepromSize - pos);
	len = ((unsigned int) len > available) ? (int) available : len;
#ifdef ESP32
	int read = (int) EEPROM.readBytes((int) pos, (void *) &b[off], len);
	pos += read;
	return read;
#else
	for (int i = 0; i < len; i++) {
		b[off + i] = EEPROM.read((int) pos++);
	}
	return len;
#endif
}

void InternalEepromInputStream::reset() {
	pos = markpos;
}

void InternalEepromInputStream::seek(unsigned int pos) {
	if (pos < eepromSize) {
		this->pos = pos;
	}
}

#endif// OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED
