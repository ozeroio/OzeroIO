/**
 * Ozero IO
 *
 * Instances of this class support both reading and writing to a random access
 * unsigned char array.
 */

#ifndef OZERO_IO_RANDOM_ACCESS_BYTE_ARRAY_H
#define OZERO_IO_RANDOM_ACCESS_BYTE_ARRAY_H 1

#include <Closeable/Closeable.h>
#include <RandomAccess/RandomAccess.h>

class RandomAccessByteArray : public RandomAccess, public virtual Closeable {

	/**
	 * Buffer used to work.
	 */
	unsigned char *buf;

	/**
	 * Buffer size.
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
	 * @param buf               The unsigned char array.
	 * @param count             The size of such unsigned char array.
	 */
	RandomAccessByteArray(unsigned char *buf, int size);

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
	unsigned int length() const;

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

#endif// OZERO_IO_RANDOM_ACCESS_BYTE_ARRAY_H
