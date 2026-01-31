/**
 * Ozero IO
 *
 * This abstract class is the superclass of all classes representing an input
 * stream of bytes.
 *
 * Applications that need to define a subclass of InputStream must always
 * provide a method that returns the next unsigned char of input.
 */

#ifndef OZERO_IO_INPUT_STREAM_H
#define OZERO_IO_INPUT_STREAM_H 1

#include <Closeable/Closeable.h>

class InputStream : public Closeable {
public:
	/**
	 * Returns the number of bytes that can be read(or skipped over) from this
	 * input stream without blocking by the next caller of a method for this input stream.
	 *
	 * @return int The number of bytes that can be read without blocking
	 */
	virtual int available();

	/**
	 * Closes this input stream and releases any system resources associated
	 * with the stream.
	 */
	void close() override;

	/**
	 * Marks the current position in this input stream.
	 */
	virtual void mark();

	/**
	 * Tests if this input stream supports the mark and reset methods.
	 *
	 * @return true if mark/reset is supported, false otherwise
	 */
	virtual bool markSupported();

	/**
	 * Tests if this input stream is currently marked.
	 *
	 * @return true if the stream is marked, false otherwise
	 */
	virtual bool isMarked();

	/**
	 * Reads the next unsigned char of data from the input stream.
	 *
	 * @return The next unsigned char of data, or -1 if end of stream is reached
	 */
	virtual int read() = 0;

	/**
	 * Reads some number of bytes from the input stream and stores them into
	 * the buffer array b.
	 *
	 * @param b The buffer to read into
	 * @param len The maximum number of bytes to read
	 * @return The number of bytes read, or -1 if end of stream is reached
	 */
	virtual int read(unsigned char *b, int len);

	/**
	 * Reads len of bytes from the stream.
	 *
	 * @param b The buffer to read into
	 * @param off The start offset in the destination array b
	 * @param len The maximum number of bytes read
	 * @return The number of bytes read, or -1 if end of stream is reached
	 */
	virtual int read(unsigned char *b, int off, int len);

	/**
	 * Repositions this stream to the position at the time the mark method was
	 * last called on this input stream.
	 */
	virtual void reset();

	/**
	 * Skips over and discards n bytes of data from this input stream.
	 *
	 * @param n The number of bytes to skip
	 * @return The actual number of bytes skipped
	 */
	virtual int skip(int n);
};

#endif// OZERO_IO_INPUT_STREAM_H
