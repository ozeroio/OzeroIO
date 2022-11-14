/**
 * Ozero IO
 * 
 * HardwareSerialOutputStream
 *
 * A software serial output stream is a output stream to write in a serial port.
 */

#if __OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED__ == 1

#ifndef __OZEROIO_IO_HARDWARE_SERIAL_OUTPUT_STREAM_H__
#define __OZEROIO_IO_HARDWARE_SERIAL_OUTPUT_STREAM_H__ 1

#include <OutputStream/OutputStream.h>
#include <SerialOutputStream/SerialOutputStream.h>

class HardwareSerialOutputStream : public SerialOutputStream {
public:

    /**
     * Public constructor.
     * 
     * @param boudRate
     */
    HardwareSerialOutputStream(unsigned int boudRate);

    /**
     * Writes the specified unsigned char to this output stream.
     */
    virtual void write(unsigned char b);
};

#endif /* __OZEROIO_IO_HARDWARE_SERIAL_OUTPUT_STREAM_H__ */

#endif /* __OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED__ */
