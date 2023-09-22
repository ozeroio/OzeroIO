#if OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "ExternalEepromOutputStream.h"

ExternalEepromOutputStream::ExternalEepromOutputStream(ExternalEeprom *externalEeprom) : externalEeprom(externalEeprom),
																						 pos(0),
																						 markPos(0),
																						 externalEepromSize(externalEeprom->getDeviceSize()) {
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
	int writtenBytes =  externalEeprom->writeBytes(pos, &b[off], len);
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
