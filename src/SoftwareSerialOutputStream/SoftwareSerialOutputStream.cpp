#if __OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED__ == 1

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

#endif /* __OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED__ */