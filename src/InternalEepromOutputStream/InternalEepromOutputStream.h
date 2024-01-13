/**
 * Ozero IO
 *
 * A resource output stream is an output stream for writing data to an
 * internal EEPROM.
 */

#if OZERO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED == 1

#ifndef OZERO_IO_INTERNAL_EEPROM_OUTPUT_STREAM_H
#define OZERO_IO_INTERNAL_EEPROM_OUTPUT_STREAM_H 1

#include <SeekableOutputStream/SeekableOutputStream.h>

class InternalEepromOutputStream : public SeekableOutputStream {

	/**
	 * Current eeprom position.
	 */
	int pos;

	/**
	 * The currently marked position in the stream.
	 */
	int markPos;

	/**
	 * Internal eeprom size.
	 */
	int eepromSize;

public:
	/**
	 * Public constructor.
	 */
	InternalEepromOutputStream();

	/**
	 * Using parent write.
	 */
	using OutputStream::write;

	/**
	 * Writes the specified unsigned char to this output stream.
	 *
	 * @param b
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

	/**
	 * Seeks to the desired position.
	 *
	 * @param pos The position we want to point to.
	 */
	void seek(int pos) override;

	/**
	 * Marks the current position in this output stream.
	 */
	void mark() override;

	/**
	 * Tests if this output stream supports the mark and reset methods.
	 */
	bool markSupported() override;

	/**
	 * Repositions this stream to the position at the time the mark method was
	 * last called on this output stream.
	 */
	void reset() override;
};

#endif// OZERO_IO_INTERNAL_EEPROM_OUTPUT_STREAM_H

#endif// OZERO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED
