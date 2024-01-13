#if OZERO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED == 1

#include "HardwareSerialOutputStream.h"

HardwareSerialOutputStream::HardwareSerialOutputStream(HardwareSerial *hardwareSerial)
	: hardwareSerial(hardwareSerial) {
}

void HardwareSerialOutputStream::write(unsigned char b) {
	hardwareSerial->write(b);
}

void HardwareSerialOutputStream::write(unsigned char *b, int len) {
	if (b == nullptr || len == 0) {
		return;
	}
	hardwareSerial->write(b, len);
}

#endif// OZERO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED
