#if OZERO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED == 1

#include "SoftwareSerialInputStream.h"

SoftwareSerialInputStream::SoftwareSerialInputStream(SoftwareSerial *softwareSerial)
	: softwareSerial(softwareSerial) {
}

int SoftwareSerialInputStream::available() {
	return softwareSerial->available();
}

int SoftwareSerialInputStream::read() {
	return softwareSerial->read();
}

int SoftwareSerialInputStream::read(unsigned char *b, int off, int len) {
	return (int) softwareSerial->readBytes(&b[off], len);
}

#endif// OZERO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED
