#if __OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED__ == 1

#include "InternalEepromOutputStream.h"
#include <EEPROM.h>

InternalEepromOutputStream::InternalEepromOutputStream() :
        pos(0), markpos(0), eepromSize(EEPROM.length()) {
}

void InternalEepromOutputStream::write(unsigned char b) {
    if (pos < eepromSize) {
        EEPROM.write((int) (pos++), b);
        EEPROM.commit();
    }
}

void InternalEepromOutputStream::write(unsigned char* b, int off, int len) {
    unsigned int available = eepromSize - pos;
    if (available < len) {
        len = (int) available;
    }
    pos += EEPROM.writeBytes((int) pos, (void *) b, len);
    EEPROM.commit();
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

#endif /* __OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED__ */
