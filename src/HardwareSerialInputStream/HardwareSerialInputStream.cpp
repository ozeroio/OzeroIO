#if OZERO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED == 1

#include "HardwareSerialInputStream.h"

HardwareSerialInputStream::HardwareSerialInputStream(HardwareSerial *hardwareSerial)
	: hardwareSerial(hardwareSerial) {
}

int HardwareSerialInputStream::available() {
	return hardwareSerial->available();
}

int HardwareSerialInputStream::read() {
	return hardwareSerial->read();
}

int HardwareSerialInputStream::read(unsigned char *b, int off, int len) {
	if (b == nullptr || len == 0) {
		return 0;
	}
#ifdef ARDUINO_ARCH_ESP32
	return (int) hardwareSerial->read(&b[off], len);
#else
	for (int i = 0; i < len; i++) {
		b[off + i] = hardwareSerial->read();
	}
	return len;
#endif
}

#endif// OZERO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED
