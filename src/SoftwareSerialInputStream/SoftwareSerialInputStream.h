/**
 * Ozero IO
 *
 * A SoftwareSerialInputStream obtains input bytes from a serial port.
 */

#if OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED == 1

#ifndef OZEROIO_IO_SOFTWARE_SERIAL_INPUT_STREAM_H
#define OZEROIO_IO_SOFTWARE_SERIAL_INPUT_STREAM_H 1

#include <InputStream/InputStream.h>
#include <SerialInputStream/SerialInputStream.h>
#include <SoftwareSerial.h>

class SoftwareSerialInputStream : public SerialInputStream {
protected:
	/**
	 * The software serial where the data will be read from.
	 */
	SoftwareSerial *softwareSerial;

public:
	/**
	 * Public constructor.
	 *
	 * @param softwareSerial an instance of SoftwareSerial
	 */
	explicit SoftwareSerialInputStream(SoftwareSerial *softwareSerial);

	/**
	 * Returns the number of bytes that can be read(or skipped over) from this
	 * input stream without blocking by the next caller of a method for this input stream.
	 */
	int available() override;

	/**
	 * Reads the next unsigned char of data from the input stream.
	 */
	int read() override;

	/**
	 * Reads len of bytes from the stream.
	 *
	 * @param b
	 * @param off
	 * @param len
	 * @return
	 */
	int read(unsigned char *b, int off, int len) override;
};

#endif// OZEROIO_IO_SOFTWARE_SERIAL_INPUT_STREAM_H

#endif// OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED
