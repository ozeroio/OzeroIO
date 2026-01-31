/**
 * Ozero IO
 *
 * Instances of this class support both reading and writing to a random access
 * externalEeprom. A random access externalEeprom behaves like a large array of bytes
 * stored in the externalEeprom system.
 */

#if OZERO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#ifndef OZERO_IO_RANDOM_ACCESS_EXTERNAL_EEPROM_H
#define OZERO_IO_RANDOM_ACCESS_EXTERNAL_EEPROM_H 1

#include <Closeable/Closeable.h>
#include <ExternalEeprom/ExternalEeprom.h>
#include <RandomAccess/RandomAccess.h>

class RandomAccessExternalEeprom : public RandomAccess, public virtual Closeable {

	/**
	 * The external eeprom to be used.
	 */
	ExternalEeprom *externalEeprom;

	/**
	 * Eeprom size.
	 */
	int size;

	/**
	 * Current position.
	 */
	int pos;

public:
	/**
	 * Public constructor.
	 *
	 * @param externalEeprom    The external eeprom instance to be used.
	 */
	explicit RandomAccessExternalEeprom(ExternalEeprom *externalEeprom);

	/**
	 * Seeks the stream at the position.
	 *
	 * @param pos       The position.
	 */
	void seek(int pos) override;

	/**
	 * Returns the length of the stream.
	 *
	 * @return          The length.
	 */
	int length() const;

	/**
	 * Closing a unsigned char array has no effect.
	 */
	void close() override;

	/**
	 * Writes a unsigned char into the stream.
	 *
	 * @param b         The unsigned char to be written.
	 */
	void write(unsigned char b) override;

	/**
	 * Writes an array of bytes into the stream.
	 *
	 * @param b         The array of bytes.
	 * @param off       The offset to be skipped when writing to b.
	 * @param len       The length of such array.
	 */
	void write(unsigned char *b, int off, int len) override;

	/**
	 * Reads the next unsigned char.
	 */
	int read() override;

	/**
	 * Reads len of bytes and stores them into the buffer array b with offset.
	 *
	 * @param b The buffer to read into
	 * @param off The offset to start writing into the buffer
	 * @param len The maximum number of bytes to read
	 * @return The number of bytes read, or -1 if end of stream is reached
	 */
	int read(unsigned char *b, int off, int len) override;

	/**
	 * Skips n bytes of the stream.
	 *
	 * @param n The number of bytes to skip
	 * @return The number of bytes actually skipped
	 */
	int skip(int n) override;
};

#endif// OZERO_IO_RANDOM_ACCESS_EXTERNAL_EEPROM_H

#endif// OZERO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED
