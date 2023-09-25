/**
 * Ozero IO
 *
 * A software serial output stream is a output stream to write in a serial port.
 */

#if OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED == 1

#ifndef OZEROIO_IO_HARDWARE_SERIAL_OUTPUT_STREAM_H
#define OZEROIO_IO_HARDWARE_SERIAL_OUTPUT_STREAM_H 1

#include <OutputStream/OutputStream.h>
#include <SerialOutputStream/SerialOutputStream.h>

class HardwareSerialOutputStream : public SerialOutputStream {
public:
	/**
	 * Public constructor.
	 *
	 * @param baudRate
	 */
	HardwareSerialOutputStream() = default;

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

#endif// OZEROIO_IO_HARDWARE_SERIAL_OUTPUT_STREAM_H

#endif// OZEROIO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED
