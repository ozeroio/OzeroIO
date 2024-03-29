/**
 * Ozero IO
 *
 * A <code>BufferedInputStream</code> adds
 * functionality to another input stream-namely,
 * the ability to buffer the input and to
 * support the <code>mark</code> and <code>reset</code>
 * methods. When  the <code>BufferedInputStream</code>
 * is created, an internal buffer array is
 * passed. As bytes from the stream are read
 * or skipped, the internal buffer is refilled
 * as necessary  from the contained input stream,
 * many bytes at a time. The <code>mark</code>
 * operation  remembers a point in the input
 * stream and the <code>reset</code> operation
 * causes all the  bytes read since the most
 * recent <code>mark</code> operation to be
 * reread before new bytes are taken from
 * the contained input stream.
 */

#ifndef OZERO_IO_BUFFERED_INPUT_STREAM_H
#define OZERO_IO_BUFFERED_INPUT_STREAM_H 1

#include <FilterInputStream/FilterInputStream.h>
#include <InputStream/InputStream.h>

class BufferedInputStream : public FilterInputStream {

	/**
	 * The size of the buffer.
	 */
	int size;

protected:
	/**
	 * The internal buffer array where the data is stored.
	 */
	unsigned char *buf;

	/**
	 * The index one greater than the index of the last valid unsigned char in the buffer.
	 * This value is always in the range <code>0</code> through <code>size</code>;
	 * elements <code>buf[0]</code>  through <code>buf[head-1]
	 * </code>contain buffered input data obtained
	 * from the underlying input stream.
	 */
	int head;

	/**
	 * The current position in the buffer. This is the index of the next
	 * character to be read from the <code>buf</code> array.
	 * <p>
	 * This value is always in the range <code>0</code>
	 * through <code>head</code>. If it is less
	 * than <code>head</code>, then  <code>buf[pos]</code>
	 * is the next unsigned char to be supplied as input;
	 * if it is equal to <code>head</code>, then
	 * the  next <code>read</code> or <code>skip</code>
	 * operation will require more bytes to be
	 * read from the contained  input stream.
	 */
	int pos;

	/**
	 * Flag to determine if there is a marker on this stream.
	 */
	bool marked;

	/**
	 * The value of the <code>pos</code> field at the time the last
	 * <code>mark</code> method was called.
	 * <p>
	 * This value is always
	 * in the range <code>0</code> through <code>pos</code>.
	 * If there is no marked position in the input
	 * stream, this field is <code>-1</code>. If
	 * there is a marked position in the input
	 * stream,  then <code>buf[markPos]</code>
	 * is the first unsigned char to be supplied as input
	 * after a <code>reset</code> operation. If
	 * <code>markPos</code> is not <code>-1</code>,
	 * then all bytes from positions <code>buf[markPos]</code>
	 * through  <code>buf[pos-1]</code> must remain
	 * in the buffer array (though they may be
	 * moved to  another place in the buffer array,
	 * with suitable adjustments to the values
	 * of <code>head</code>,  <code>pos</code>,
	 * and <code>markPos</code>); they may not
	 * be discarded unless and until the difference
	 * between <code>pos</code> and <code>markPos</code>
	 * exceeds <code>marklimit</code>.
	 */
	int markPos;

public:
	/**
	 * Public constructor.
	 *
	 * @param in
	 * @param buf
	 * @param size
	 */
	BufferedInputStream(InputStream *inputStream, unsigned char *buf, int size);

	/**
	 * Virtual destructor.
	 */
	virtual ~BufferedInputStream() = default;

	/**
	 * Returns the number of bytes that can be read(or skipped over) from this
	 * input stream without blocking by the next caller of a method for this input stream.
	 *
	 */
	int available() override;

	/**
	 * Closes this input stream and releases any system resources associated
	 * with the stream.
	 */
	void close() override;

	/**
	 * Marks the current position in this input stream.
	 *
	 * NOTE: Mark position is only supported when within the current buffet.
	 */
	void mark() override;

	/**
	 * Tests if this input stream supports the mark and reset methods.
	 *
	 * NOTE: Mark position is only supported when within the current buffet.
	 */
	bool markSupported() override;

	/**
	 * Reads the next unsigned char of data from the input stream.
	 */
	int read() override;

	/**
	 * Reads some number of bytes from the input stream and stores them into
	 * the buffer array b.
	 *
	 * @param b
	 * @param len
	 * @return
	 */
	int read(unsigned char *b, int len) override;

	/**
	 * Reads some number of bytes from the input stream and stores them into
	 * the buffer array b.
	 */
	int read(unsigned char *b, int off, int len) override;

	/**
	 * Repositions this stream to the position at the time the mark method was
	 * last called on this input stream.
	 *
	 * NOTE: Mark position is only supported when within the current buffet.
	 */
	void reset() override;

	/**
	 * Skips over and discards n bytes of data from this input stream.
	 */
	int skip(int n) override;

private:
	/**
	 * Reads a chunk to the a portion of an array, reading from the underlying
	 * stream at most once if necessary.
	 *
	 * @param b
	 * @param off
	 * @param len
	 */
	int readPortion(unsigned char *b, int off, int len);

	/**
	 * Moves the valid bytes on the buffer to the left side of the buffer.
	 */
	void shiftBuffer();

	/**
	 * Fills the buffer.
	 */
	void fillBuffer();
};

#endif// OZERO_IO_BUFFERED_INPUT_STREAM_H
