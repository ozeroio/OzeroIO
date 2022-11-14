/**
 * Ozero IO
 * 
 * SoftwareSerialInputStream
 * 
 * A SoftwareSerialInputStream obtains input bytes from a serial port.
 */

#if __OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED__ == 1

#ifndef __OZEROIO_IO_SOFTWARE_SERIAL_INPUT_STREAM_H__
#define __OZEROIO_IO_SOFTWARE_SERIAL_INPUT_STREAM_H__ 1

#include <SoftwareSerial/SoftwareSerial.h>
#include <InputStream/InputStream.h>
#include <SerialInputStream/SerialInputStream.h>

class SoftwareSerialInputStream : public SerialInputStream {
protected:

    /**
     * The software serial where the data will be read.
     */
    SoftwareSerial *softwareSerial;

public:

    /**
     * Public constructor.
     * 
     * @param serial
     * @param boudRate
     */
    SoftwareSerialInputStream(SoftwareSerial *softwareSerial);

    /**
     * Returns the number of bytes that can be read(or skipped over) from this 
     * input stream without blocking by the next caller of a method for this input stream.
     */
    virtual int available();

    /**
     * Reads the next unsigned char of data from the input stream.
     */
    virtual int read();

    /**
     * Reads len of bytes from the stream.
     *
     * @param b
     * @param off
     * @param len
     * @return
     */
    virtual int read(unsigned char* b, int off, int len);
};

#endif /* __OZEROIO_IO_SOFTWARE_SERIAL_INPUT_STREAM_H__ */

#endif /* __OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED__ */
