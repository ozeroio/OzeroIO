#if OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#include "ExternalEepromInputStream.h"

ExternalEepromInputStream::ExternalEepromInputStream(ExternalEeprom* externalEeprom)
        : maxAvailableChunk(0x08), externalEeprom(externalEeprom), pos(0), markpos(0),
        externalEepromSize(externalEeprom->getDeviceSize()) {
}

int ExternalEepromInputStream::available() {
    int room = externalEepromSize - pos;
    if (room > maxAvailableChunk) {
        return maxAvailableChunk;
    }
    return room;
}

int ExternalEepromInputStream::read() {
    if (pos >= externalEepromSize) {
        return -1;
    }
    return (int) externalEeprom->read(pos++);
}

int ExternalEepromInputStream::read(unsigned char *b, const int off, const int len) {
    unsigned int available = (externalEepromSize - pos);
    int total = externalEeprom->readBytes(pos, &b[off], ozero_min(len, available));
    pos += total;
    return total;
}

void ExternalEepromInputStream::mark() {
    markpos = pos;
}

bool ExternalEepromInputStream::markSupported() {
    return true;
}

void ExternalEepromInputStream::reset() {
    pos = markpos;
}

void ExternalEepromInputStream::seek(const unsigned int pos) {
    this->pos = ozero_min(pos, externalEepromSize - 1);
}

#endif // OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED