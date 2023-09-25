/**
 * Ozero IO
 *
 *
 * Instances of this class support both reading and writing to the internal EEPROM.
 * A random access InternalEeprom behaves like a large array of bytes
 * stored in the EEPROM system.
 */

#if OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED == 1

#ifndef OZEROIO_IO_RANDOM_ACCESS_INTERNAL_EEPROM_H
#define OZEROIO_IO_RANDOM_ACCESS_INTERNAL_EEPROM_H 1

#include <Closeable/Closeable.h>
#include <RandomAccess/RandomAccess.h>

class RandomAccessInternalEeprom : public RandomAccess, public virtual Closeable {

	/**
	 * Current position.
	 */
	int pos;

	/**
	 * Start position.
	 */
	int startPos;

	/**
	 * End position.
	 */
	int endPos;

	/**
	 * The size of this internal eeprom.
	 */
	int size;

public:
	/**
	 * Public constructor.
	 *
	 * @param externalEeprom    The external eeprom instance to be used.
	 */
	RandomAccessInternalEeprom(int startPos, int endPos);

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
	 * @param b
	 * @param off
	 * @param len
	 * @return
	 */
	int read(unsigned char *b, int off, int len) override;

	/**
	 * Skips n bytes of the stream.
	 *
	 * @param n
	 * @return int The number of skipped bytes.
	 */
	int skip(int n) override;
};

#endif// OZEROIO_IO_RANDOM_ACCESS_INTERNAL_EEPROM_H

#endif// OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED
