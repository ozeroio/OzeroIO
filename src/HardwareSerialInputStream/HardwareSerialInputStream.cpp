#if OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED == 1

#include "HardwareSerialInputStream.h"
#include <Arduino.h>

int HardwareSerialInputStream::available() {
	return Serial.available();
}

int HardwareSerialInputStream::read() {
	return Serial.read();
}

int HardwareSerialInputStream::read(unsigned char *b, int off, int len) {
	if (b == nullptr || len == 0) {
		return 0;
	}
#ifdef ESP32
	return (int) Serial.read(&b[off], len);
#else
	for (int i = 0; i < len; i++) {
		b[off + i] = Serial.read();
	}
	return len;
#endif
}

#endif// OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED
