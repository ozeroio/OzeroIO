/**
 * Ozero IO
 * 
 * SoftwareSerialOutputStream
 *
 * A software serial output stream is a output stream to write in a serial port.
 */

#if __OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED__ == 1

#ifndef __OZEROIO_IO_SOFTWARE_SERIAL_OUTPUT_STREAM_H__
#define __OZEROIO_IO_SOFTWARE_SERIAL_OUTPUT_STREAM_H__ 1

#include <SoftwareSerial/SoftwareSerial.h>
#include <OutputStream/OutputStream.h>
#include <SerialOutputStream/SerialOutputStream.h>

class SoftwareSerialOutputStream : public SerialOutputStream {
protected:

    /* 
     * The software serial where data is written.
     */
    SoftwareSerial *softwareSerial;

public:

    SoftwareSerialOutputStream(SoftwareSerial *softwareSerial);

    /**
     * Writes the specified unsigned char to this output stream.
     */
    virtual void write(unsigned char b);

    /**
     * Writes len bytes from the specified unsigned char array starting at offset off to
     * this output stream.
     *
     * @param b
     * @param off
     * @param len
     */
    virtual void write(unsigned char* b, int off, int len);
};

#endif /* __OZEROIO_IO_SOFTWARE_SERIAL_OUTPUT_STREAM_H__ */

#endif /* __OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED__ */
