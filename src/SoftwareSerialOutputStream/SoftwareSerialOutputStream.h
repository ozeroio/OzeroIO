/**
 * Ozero IO
 *
 * A software serial output stream is a output stream to write in a serial port.
 */

#if OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED == 1

#ifndef OZEROIO_IO_SOFTWARE_SERIAL_OUTPUT_STREAM_H
#define OZEROIO_IO_SOFTWARE_SERIAL_OUTPUT_STREAM_H 1

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
	explicit SoftwareSerialOutputStream(SoftwareSerial *softwareSerial);

	/**
	 * Writes the specified unsigned char to this output stream.
	 */
	void write(unsigned char b) override;

	/**
	 * Writes len bytes from the specified unsigned char array starting at offset off to
	 * this output stream.
	 *
	 * @param b
	 * @param off
	 * @param len
	 */
	void write(unsigned char *b, int off, int len) override;
};

#endif// OZEROIO_IO_SOFTWARE_SERIAL_OUTPUT_STREAM_H

#endif// OZEROIO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED
