/**
 * Ozero IO
 * 
 * HardwareSerialInputStream
 * 
 * A HardwareSerialInputStream obtains input bytes from a serial port.
 */

#if __OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED__ == 1

#ifndef __OZEROIO_IO_HARDWARE_SERIAL_INPUT_STREAM_H__
#define __OZEROIO_IO_HARDWARE_SERIAL_INPUT_STREAM_H__ 1

#include <InputStream/InputStream.h>
#include <SerialInputStream/SerialInputStream.h>

class HardwareSerialInputStream : public SerialInputStream {
public:

    /**
     * Public constructor.
     * 
     * @param baudRate
     */
    HardwareSerialInputStream(unsigned int baudRate);

    /**
     * Returns the number of bytes that can be read(or skipped over) from this 
     * input stream without blocking by the next caller of a method for this input stream.
     */
    virtual int available();

    /**
     * Reads the next unsigned char of data from the input stream.
     */
    virtual int read();
};

#endif /* __OZEROIO_IO_HARDWARE_SERIAL_INPUT_STREAM_H__ */

#endif /* __OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED__ */
