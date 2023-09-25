#if OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "InternalEepromOutputStream.h"
#include <EEPROM.h>
#include <io.h>
#include <limits.h>

InternalEepromOutputStream::InternalEepromOutputStream() : pos(0),
														   markPos(0) {
	auto size = EEPROM.length();

	// Int is used to address the stream, so lets make sure we don't overflow in any 16bit int archs.
	eepromSize = (size > INT_MAX) ? INT_MAX : (int) size;
}

void InternalEepromOutputStream::write(unsigned char b) {
	if (pos < eepromSize) {
		EEPROM.write(pos++, b);
#ifdef ESP32
		EEPROM.commit();
#endif
	}
}

void InternalEepromOutputStream::write(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return;
	}
	const int n = ozero_min(eepromSize - pos, len);
#ifdef ESP32
	pos += (int) EEPROM.writeBytes(pos, &b[off], n);
	EEPROM.commit();
#else
	for (int i = 0; i < n; i++) {
		EEPROM.write(pos++, b[off + i]);
	}
#endif
}

void InternalEepromOutputStream::seek(int pos) {
	if (pos < eepromSize) {
		this->pos = pos;
	}
}

void InternalEepromOutputStream::mark() {
	markPos = pos;
}

bool InternalEepromOutputStream::markSupported() {
	return true;
}

void InternalEepromOutputStream::reset() {
	pos = markPos;
}

#endif// OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED
