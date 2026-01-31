/**
 * Ozero IO
 *
 * A ByteArrayInputStream contains an internal buffer that
 * contains bytes that may be read from the stream.
 */

#ifndef OZERO_IO_BYTE_ARRAY_INPUT_STREAM_H
#define OZERO_IO_BYTE_ARRAY_INPUT_STREAM_H 1

#include <SeekableInputStream/SeekableInputStream.h>

class ByteArrayInputStream : public virtual SeekableInputStream {

protected:
	/*
	 * The buffer where data is stored.
	 */
	unsigned char *buf;

	/*
	 * The number of valid bytes in the buffer.
	 */
	int size;

	/*
	 * Current position
	 */
	int pos;

	/*
	 * The currently marked position in the stream.
	 */
	int markPos;

public:
	ByteArrayInputStream(unsigned char *buf, int size);

	/**
	 * Returns the number of bytes that can be read (or skipped over) from this input stream.
	 *
	 * @return int The number of bytes that can be read without blocking
	 */
	int available() override;

	/**
	 * Marks the current position in this input stream.
	 */
	void mark() override;

	/**
	 * Tests if this input stream supports the mark and reset methods.
	 *
	 * @return true if mark/reset is supported, false otherwise
	 */
	bool markSupported() override;

	/**
	 * Using the parent's read.
	 */
	using InputStream::read;

	/**
	 * Reads the next unsigned char of data from the input stream.
	 *
	 * @return int The next unsigned char of data, or -1 if end of stream is reached
	 */
	int read() override;

	/**
	 * Reads up to <code>len</code> bytes of data from this buffer.
	 * <p>
	 *
	 * @param b the buffer into which the data is read.
	 * @param off the start offset in the destination array <code>b</code>
	 * @param len the maximum number of bytes read.
	 * @return the total number of bytes read into the buffer, or <code>-1</code>
	 * if there is no more data because the end of the stream has been reached.
	 */
	int read(unsigned char *b, int off, int len) override;

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

#endif// OZERO_IO_BYTE_ARRAY_INPUT_STREAM_H
