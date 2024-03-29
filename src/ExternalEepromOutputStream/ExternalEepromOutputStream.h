/**
 * Ozero IO
 *
 * A resource output stream is an output stream for writing data to an
 * ExternalEeprom.
 */

// #if OZERO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#ifndef OZERO_IO_EXTERNAL_EEPROM_OUTPUT_STREAM_H
#define OZERO_IO_EXTERNAL_EEPROM_OUTPUT_STREAM_H 1

#include <ExternalEeprom/ExternalEeprom.h>
#include <SeekableOutputStream/SeekableOutputStream.h>

class ExternalEepromOutputStream : public SeekableOutputStream {

	/**
	 * The associated eeprom.
	 */
	ExternalEeprom *externalEeprom;

	/**
	 * Current eeprom position.
	 */
	int pos;

	/**
	 * The currently marked position in the stream.
	 */
	int markPos;

	/*
	 * The size of the externalEeprom.
	 */
	int externalEepromSize;

public:
	/**
	 * Public constructor.
	 *
	 * @param externalEeprom
	 */
	explicit ExternalEepromOutputStream(ExternalEeprom *externalEeprom);

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

#endif// OZERO_IO_EXTERNAL_EEPROM_OUTPUT_STREAM_H

// #endif // OZERO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED
