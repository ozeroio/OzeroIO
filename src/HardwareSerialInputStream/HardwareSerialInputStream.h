/**
 * Ozero IO
 *
 * A hardware serial input stream obtains input bytes from a serial port.
 */

#if OZERO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED == 1

#ifndef OZERO_IO_HARDWARE_SERIAL_INPUT_STREAM_H
#define OZERO_IO_HARDWARE_SERIAL_INPUT_STREAM_H 1

#include <HardwareSerial.h>
#include <InputStream/InputStream.h>
#include <SerialInputStream/SerialInputStream.h>

class HardwareSerialInputStream : public SerialInputStream {

	HardwareSerial *hardwareSerial;

public:
	/**
	 * Public constructor.
	 *
	 * @param hardwareSerial
	 */
	explicit HardwareSerialInputStream(HardwareSerial *hardwareSerial);

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

	using InputStream::read;
};

#endif// OZERO_IO_HARDWARE_SERIAL_INPUT_STREAM_H

#endif// OZERO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED
