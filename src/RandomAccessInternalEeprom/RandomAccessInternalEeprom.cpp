#if OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "RandomAccessInternalEeprom.h"
#include <EEPROM.h>
#include <io.h>

RandomAccessInternalEeprom::RandomAccessInternalEeprom(int startPos, int endPos) : pos(startPos),
																				   startPos(startPos),
																				   endPos(endPos),
																				   size(endPos - startPos) {
}

int RandomAccessInternalEeprom::length() const {
	return size;
}

void RandomAccessInternalEeprom::seek(const int pos) {
	if (pos < size) {
		this->pos = pos;
	}
}

void RandomAccessInternalEeprom::close() {
}

void RandomAccessInternalEeprom::write(const unsigned char b) {
	if (pos < size) {
		EEPROM.write(pos++, b);
#ifdef ESP32
		EEPROM.commit();
#endif
	}
}

void RandomAccessInternalEeprom::write(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return;
	}
	const int n = ozero_min(size - pos, len);
#ifdef ESP32
	pos += (int) EEPROM.writeBytes(pos, &b[off], n);
	EEPROM.commit();
#else
	for (int i = 0; i < n; i++) {
		EEPROM.write(pos++, b[off + i]);
	}
#endif
}

int RandomAccessInternalEeprom::read() {
	if (pos >= size) {
		return -1;
	}
	return (int) EEPROM.read(pos++);
}

int RandomAccessInternalEeprom::read(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return 0;
	}
	const int n = ozero_min(size - pos, len);
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

int RandomAccessInternalEeprom::skip(const int n) {
	int newPos = pos + n;
	if (newPos > size) {
		newPos = size;
	}
	const int skipped = newPos - pos;
	pos = newPos;
	return skipped;
}

#endif// OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED
