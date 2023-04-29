#if OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED == 1

#include "SoftwareSerialOutputStream.h"

SoftwareSerialOutputStream::SoftwareSerialOutputStream(SoftwareSerial *softwareSerial) :
        softwareSerial(softwareSerial) {
}

void SoftwareSerialOutputStream::write(unsigned char b) {
    softwareSerial->write(b);
}

void SoftwareSerialOutputStream::write(unsigned char* b, int off, int len) {
    softwareSerial->write(&b[off], len);
}

#endif // OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED