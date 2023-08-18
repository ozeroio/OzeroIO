#if OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED == 1

#include "HardwareSerialInputStream.h"
#include <Arduino.h>

HardwareSerialInputStream::HardwareSerialInputStream(unsigned int baudRate) {
	Serial.begin(baudRate);
}

int HardwareSerialInputStream::available() {
	return Serial.available();
}

int HardwareSerialInputStream::read() {
	return Serial.read();
}

#endif// OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED
