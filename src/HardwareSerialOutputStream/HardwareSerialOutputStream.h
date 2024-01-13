/**
 * Ozero IO
 *
 * A hardware serial output stream is a output stream to write in a serial port.
 */

#if OZERO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED == 1

#ifndef OZERO_IO_HARDWARE_SERIAL_OUTPUT_STREAM_H
#define OZERO_IO_HARDWARE_SERIAL_OUTPUT_STREAM_H 1

#include <HardwareSerial.h>
#include <OutputStream/OutputStream.h>
#include <SerialOutputStream/SerialOutputStream.h>

class HardwareSerialOutputStream : public SerialOutputStream {

	HardwareSerial *hardwareSerial;

public:
	/**
	 * Public constructor.
	 *
	 * @param hardwareSerial
	 */
	explicit HardwareSerialOutputStream(HardwareSerial *hardwareSerial);

	/**
	 * Writes the specified unsigned char to this output stream.
	 */
	void write(unsigned char b) override;

	/**
	 * Writes len bytes from the specified unsigned char array to
	 * this output stream.
	 *
	 * @param b
	 * @param len
	 */
	void write(unsigned char *b, int len) override;

	using OutputStream::write;
};

#endif// OZERO_IO_HARDWARE_SERIAL_OUTPUT_STREAM_H

#endif// OZERO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED
