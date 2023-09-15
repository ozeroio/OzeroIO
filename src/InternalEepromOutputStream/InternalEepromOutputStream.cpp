#if OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "InternalEepromOutputStream.h"
#include <EEPROM.h>
#include <io.h>

InternalEepromOutputStream::InternalEepromOutputStream() : pos(0), markpos(0), eepromSize(EEPROM.length()) {
}

void InternalEepromOutputStream::write(unsigned char b) {
	if (pos < eepromSize) {
		EEPROM.write((int) (pos++), b);
#ifdef ESP32
		EEPROM.commit();
#endif
	}
}

void InternalEepromOutputStream::write(unsigned char *b, int off, int len) {
	unsigned int available = eepromSize - pos;
	len = ozero_min(len, available);
#ifdef ESP32
	pos += EEPROM.writeBytes((int) pos, (void *) &(b[off]), len);
	EEPROM.commit();
#else
	for (int i = 0; i < len; i++) {
		EEPROM.write((int) pos++, b[off + i]);
	}
#endif
}

void InternalEepromOutputStream::seek(unsigned int pos) {
	if (pos < eepromSize) {
		this->pos = pos;
	}
}

void InternalEepromOutputStream::mark() {
	markpos = pos;
}

bool InternalEepromOutputStream::markSupported() {
	return true;
}

void InternalEepromOutputStream::reset() {
	pos = markpos;
}

#endif// OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED
