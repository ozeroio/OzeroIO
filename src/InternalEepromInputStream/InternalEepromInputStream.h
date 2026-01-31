/**
 * Ozero IO
 *
 * An InternalEepromInputStream obtains input bytes from the internal EEPROM.
 */

#if OZERO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED == 1

#ifndef OZERO_IO_INTERNAL_EEPROM_INPUT_STREAM_H
#define OZERO_IO_INTERNAL_EEPROM_INPUT_STREAM_H 1

#include <EEPROM.h>
#include <SeekableInputStream/SeekableInputStream.h>

class InternalEepromInputStream : public virtual SeekableInputStream {

protected:
	/**
	 * Current position
	 */
	int pos;

	/**
	 * The currently marked position in the stream.
	 */
	int markPos;

	/**
	 * The size of the eeprom.
	 */
	int eepromSize;

public:
	/**
	 * Public constructor.
	 */
	InternalEepromInputStream();

	/**
	 * Returns the number of bytes that can be read(or skipped over) from this
	 * input stream without blocking by the next caller of a method for this
	 * input stream.
	 *
	 * @return int      The available number of bytes.
	 */
	int available() override;

	/**
	 * Using the parent read.
	 */
	using InputStream::read;

	/**
	 * Reads the next unsigned char of data from the input stream.
	 *
	 * @return int      The read unsigned char as an int.
	 */
	int read() override;

	/**
	 * Reads len of bytes from the input stream.
	 *
	 * @param b The buffer to read into
	 * @param off The offset to start writing into the buffer
	 * @param len The maximum number of bytes to read
	 * @return The number of bytes read, or -1 if end of stream is reached
	 */
	int read(unsigned char *b, int off, int len) override;

	/**
	 * Marks the current position in this input stream.
	 */
	void mark() override;

	/**
	 * Tests if this input stream supports the mark and reset methods.
	 *
	 * @return bool
	 */
	bool markSupported() override;

	/**
	 * Repositions this stream to the position at the time the mark method was
	 * last called on this input stream.
	 */
	void reset() override;

	/**
	 * Seeks to the desired position.
	 *
	 * @param pos The position we want to point to.
	 */
	void seek(int pos) override;
};

#endif// OZERO_IO_INTERNAL_EEPROM_INPUT_STREAM_H

#endif// OZERO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED
