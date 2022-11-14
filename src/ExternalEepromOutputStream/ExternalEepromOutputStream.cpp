#if __OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED__ == 1

#include "ExternalEepromOutputStream.h"

ExternalEepromOutputStream::ExternalEepromOutputStream(ExternalEeprom* externalEeprom)
        : externalEeprom(externalEeprom), pos(0), markpos(0), externalEepromSize(externalEeprom->getDeviceSize()) {
}

void ExternalEepromOutputStream::write(unsigned char b) {
    externalEeprom->write(pos++, b);
}

void ExternalEepromOutputStream::write(unsigned char* b, int off, int len) {
    externalEeprom->writeBytes(pos, &b[off], len);
    pos += len;
}

void ExternalEepromOutputStream::seek(unsigned int pos) {
    if (pos < externalEepromSize) {
        this->pos = pos;
    }
}

void ExternalEepromOutputStream::mark() {
    markpos = pos;
}

bool ExternalEepromOutputStream::markSupported() {
    return true;
}

void ExternalEepromOutputStream::reset() {
    pos = markpos;
}

#endif /* __OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED__ */
