/**
 * Ozero IO
 *
 * A software serial output stream is a output stream to write in a serial port.
 */

#if OZERO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED == 1

#ifndef OZERO_IO_SOFTWARE_SERIAL_OUTPUT_STREAM_H
#define OZERO_IO_SOFTWARE_SERIAL_OUTPUT_STREAM_H 1

#include <OutputStream/OutputStream.h>
#include <SerialOutputStream/SerialOutputStream.h>
#include <SoftwareSerial.h>

class SoftwareSerialOutputStream : public SerialOutputStream {
protected:
	/*
	 * The software serial where data is written.
	 */
	SoftwareSerial *softwareSerial;

public:
	/**
	 * Public constructor.
	 *
	 * @param softwareSerial The software serial instance to write to
	 */
	explicit SoftwareSerialOutputStream(SoftwareSerial *softwareSerial);

	/**
	 * Writes the specified unsigned char to this output stream.
	 *
	 * @param b The unsigned char to be written
	 */
	void write(unsigned char b) override;

	/**
	 * Writes len bytes from the specified unsigned char array starting at offset off to
	 * this output stream.
	 *
	 * @param b The array of bytes to write
	 * @param off The start offset in the array
	 * @param len The number of bytes to write
	 */
	void write(unsigned char *b, int off, int len) override;
};

#endif// OZERO_IO_SOFTWARE_SERIAL_OUTPUT_STREAM_H

#endif// OZERO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED
