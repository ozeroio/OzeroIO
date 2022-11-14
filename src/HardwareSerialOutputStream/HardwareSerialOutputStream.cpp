#if __OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED__ == 1

#include "HardwareSerialOutputStream.h"

HardwareSerialOutputStream::HardwareSerialOutputStream(unsigned int boudRate) {
    Serial.begin(boudRate);
}

void HardwareSerialOutputStream::write(unsigned char b) {
    Serial.write(b);
}

#endif /* __OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED__ */
