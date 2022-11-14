#if __OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED__ == 1

#include "SoftwareSerialInputStream.h"

SoftwareSerialInputStream::SoftwareSerialInputStream(SoftwareSerial *softwareSerial) :
        softwareSerial(softwareSerial) {
}

int SoftwareSerialInputStream::available() {
    return softwareSerial->available();
}

int SoftwareSerialInputStream::read() {
    return softwareSerial->read();
}

int SoftwareSerialInputStream::read(unsigned char* b, int off, int len) {
    return softwareSerial->readBytes(&b[off], len);
}

#endif /* __OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED__ */
