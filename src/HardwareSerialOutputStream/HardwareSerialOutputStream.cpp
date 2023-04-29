#if OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED == 1

#include "HardwareSerialOutputStream.h"
#include <Arduino.h>

HardwareSerialOutputStream::HardwareSerialOutputStream(unsigned int baudRate) {
    Serial.begin(baudRate);
}

void HardwareSerialOutputStream::write(unsigned char b) {
    Serial.write(b);
}

void HardwareSerialOutputStream::write(unsigned char* b, int len) {
    Serial.write(b, len);
}

#endif // OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED
