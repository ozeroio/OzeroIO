#if OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "ExternalEepromOutputStream.h"
#include <limits.h>

ExternalEepromOutputStream::ExternalEepromOutputStream(ExternalEeprom *externalEeprom) : externalEeprom(externalEeprom),
																						 pos(0),
																						 markPos(0) {

	auto size = externalEeprom->getDeviceSize();

	// Int is used to address the stream, so lets make sure we don't overflow in any 16bit int archs.
	externalEepromSize = (size > INT_MAX) ? INT_MAX : size;
}

void ExternalEepromOutputStream::write(unsigned char b) {
	if (pos < externalEepromSize) {
		externalEeprom->write(pos++, b);
	}
}

void ExternalEepromOutputStream::write(unsigned char *b, int off, int len) {
	if (b == nullptr || len == 0) {
		return;
	}
	const int writtenBytes = (int) externalEeprom->writeBytes(pos, &b[off], len);
	pos += writtenBytes;
}

void ExternalEepromOutputStream::seek(int pos) {
	if (pos < externalEepromSize) {
		this->pos = pos;
	}
}

void ExternalEepromOutputStream::mark() {
	markPos = pos;
}

bool ExternalEepromOutputStream::markSupported() {
	return true;
}

void ExternalEepromOutputStream::reset() {
	pos = markPos;
}

#endif// OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED
