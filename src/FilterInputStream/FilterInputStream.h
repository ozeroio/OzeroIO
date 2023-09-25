/**
 * Ozero IO
 *
 * A <code>FilterInputStream</code> contains
 * some other input stream, which it uses as
 * its  basic source of data, possibly transforming
 * the data along the way or providing  additional
 * functionality. The class <code>FilterInputStream</code>
 * itself simply overrides all  methods of
 * <code>InputStream</code> with versions that
 * pass all requests to the contained  input
 * stream. Subclasses of <code>FilterInputStream</code>
 * may further override some of  these methods
 * and may also provide additional methods
 * and fields.
 */

#ifndef OZEROIO_IO_FILTER_INPUT_STREAM_H
#define OZEROIO_IO_FILTER_INPUT_STREAM_H 1

#include <InputStream/InputStream.h>

class FilterInputStream : public virtual InputStream {

protected:
	/**
	 * The input stream to be filtered.
	 */
	InputStream *inputStream;

	/**
	 * Creates a <code>FilterInputStream</code>
	 * by assigning the  argument <code>in</code>
	 * to the field <code>this->in</code> so as
	 * to remember it for later use.
	 *
	 * @param   in   the underlying input stream
	 */
	explicit FilterInputStream(InputStream *inputStream);

public:
	/**
	 * Reads the next unsigned char of data from this input stream. The value
	 * unsigned char is returned as an <code>int</code> in the range
	 * <code>0</code> to <code>255</code>. If no unsigned char is available
	 * because the end of the stream has been reached, the value
	 * <code>-1</code> is returned.
	 * <p>
	 * This method
	 * simply performs <code>inputStream->read()</code> and returns the result.
	 *
	 * @return     the next unsigned char of data, or <code>-1</code> if the end of the
	 *             stream is reached.
	 */
	int read() override;

	/**
	 * Reads up to <code>len</code> bytes of data from this
	 * input stream into an array of bytes.
	 * <p>
	 * This method simply performs the call
	 * <code>read(b, 0, len)</code> and returns
	 * the  result. It is important that it does
	 * <i>not</i> do <code>inputStream->read(b)</code> instead;
	 * certain subclasses of  <code>FilterInputStream</code>
	 * depend on the implementation strategy actually
	 * used.
	 *
	 * @param      b   the buffer into which the data is read.
	 * @return     the total number of bytes read into the buffer, or
	 *             <code>-1</code> if there is no more data because the end of
	 *             the stream has been reached.
	 */
	int read(unsigned char *b, int len) override;

	/**
	 * Reads up to <code>len</code> bytes of data from this input stream
	 * into an array of bytes.
	 * <p>
	 * This method simply performs <code>inputStream->read(b, off, len)</code>
	 * and returns the result.
	 *
	 * @param      b     the buffer into which the data is read.
	 * @param      off   the start offset in the destination array <code>b</code>
	 * @param      len   the maximum number of bytes read.
	 * @return     the total number of bytes read into the buffer, or
	 *             <code>-1</code> if there is no more data because the end of
	 *             the stream has been reached.
	 */
	int read(unsigned char *b, int off, int len) override;

	/**
	 * This method simply performs <code>inputStream->skip(n)</code>.
	 *
	 * @param
	 */
	int skip(int n) override;

	/**
	 * Returns an estimate of the number of bytes that can be read (or
	 * skipped over) from this input stream without blocking by the next
	 * caller of a method for this input stream.
	 *
	 * @return     an estimate of the number of bytes that can be read (or skipped
	 *             over) from this input stream without blocking.
	 */
	int available() override;

	/**
	 * Closes this input stream.
	 * This method simply performs <code>inputStream->close()</code>.
	 */
	void close() override;

	/**
	 * Marks the current position in this input stream. A subsequent
	 * call to the <code>reset</code> method repositions this stream at
	 * the last marked position so that subsequent reads re-read the same bytes.
	 * <p>
	 * This method simply performs <code>inputStream->mark()</code>.
	 */
	void mark() override;

	/**
	 * Repositions this stream to the position at the time the
	 * <code>mark</code> method was last called on this input stream.
	 * <p>
	 * This method simply performs <code>inputStream->reset()</code>.
	 * <p>
	 * Stream marks are intended to be used in
	 * situations where you need to read ahead a little to see what's in
	 * the stream. Often this is most easily done by invoking some
	 * general parser. If the stream is of the type handled by the
	 * parse, it just chugs along happily. If the stream is not of
	 * that type, the parser should toss an exception when it fails.
	 */
	void reset() override;

	/**
	 * Tests if this input stream supports the <code>mark</code>
	 * and <code>reset</code> methods.
	 * This method
	 * simply performs <code>inputStream->markSupported()</code>.
	 *
	 * @return  <code>true</code> if this stream type supports the
	 *          <code>mark</code> and <code>reset</code> method;
	 *          <code>false</code> otherwise.
	 */
	bool markSupported() override;
};

#endif// OZEROIO_IO_FILTER_INPUT_STREAM_H
