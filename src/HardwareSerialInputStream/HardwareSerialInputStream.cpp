#if __OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED__ == 1

#include "HardwareSerialInputStream.h"

HardwareSerialInputStream::HardwareSerialInputStream(unsigned int baudRate) {
    Serial.begin(baudRate);
}

int HardwareSerialInputStream::available() {
    return Serial.available();
}

int HardwareSerialInputStream::read() {
    if (available() > 0) {
        return Serial.read();
    }
    return -1;
}

#endif /* __OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED__ */
