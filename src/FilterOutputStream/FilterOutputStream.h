/**
 * Ozero IO
 *
 * This class is the superclass of all classes that filter output
 * streams. These streams sit on top of an already existing output
 * stream (the <i>underlying</i> output stream) which it uses as its
 * basic sink of data, but possibly transforming the data along the
 * way or providing additional functionality.
 * <p>
 * The class <code>FilterOutputStream</code> itself simply overrides
 * all methods of <code>OutputStream</code> with versions that pass
 * all requests to the underlying output stream. Subclasses of
 * <code>FilterOutputStream</code> may further override some of these
 * methods as well as provide additional methods and fields.
 */

#ifndef OZERO_IO_FILTER_OUTPUT_STREAM_H
#define OZERO_IO_FILTER_OUTPUT_STREAM_H 1

#include <OutputStream/OutputStream.h>

class FilterOutputStream : public OutputStream {
protected:
	/**
	 * The underlying output stream to be filtered.
	 */
	OutputStream *outputStream;

	/**
	 * Creates an output stream filter built on top of the specified
	 * underlying output stream.
	 *
	 * @param   outputStream   the underlying output stream to be assigned to
	 *                		   the field <tt>this->out</tt> for later use.
	 */
	explicit FilterOutputStream(OutputStream *outputStream);

public:
	/**
	 * Writes the specified <code>unsigned char</code> to this output stream.
	 * <p>
	 * The <code>write</code> method of <code>FilterOutputStream</code>
	 * calls the <code>write</code> method of its underlying output stream,
	 * that is, it performs <tt>outputStream->write(b)</tt>.
	 * <p>
	 * Implements the abstract <tt>write</tt> method of <tt>OutputStream</tt>.
	 *
	 * @param      b   the <code>unsigned char</code>.
	 */
	void write(unsigned char b) override;

	/**
	 * Writes <code>len</code> bytes to this output stream.
	 * <p>
	 * The <code>write</code> method of <code>FilterOutputStream</code>
	 * calls its <code>write</code> method of two arguments with the
	 * arguments <code>b</code> and
	 * <codelen</code>.
	 *
	 * @param      b   the data to be written.
	 * @param      len the length
	 */
	void write(unsigned char *b, int len) override;

	/**
	 * Writes <code>len</code> bytes from the specified
	 * <code>unsigned char</code> array starting at offset <code>off</code> to
	 * this output stream.
	 *
	 * @param      b     the data.
	 * @param      off   the start offset in the data.
	 * @param      len   the number of bytes to write.
	 */
	void write(unsigned char *b, int off, int len) override;

	/**
	 * Flushes this output stream and forces any buffered output bytes
	 * to be written out to the stream.
	 * <p>
	 * The <code>flush</code> method of <code>FilterOutputStream</code>
	 * calls the <code>flush</code> method of its underlying output stream.
	 */
	void flush() override;

	/**
	 * Closes this output stream and releases any system resources
	 * associated with the stream.
	 * <p>
	 * The <code>close</code> method of <code>FilterOutputStream</code>
	 * calls its <code>flush</code> method, and then calls the
	 * <code>close</code> method of its underlying output stream.
	 */
	void close() override;

	/**
	 * Marks the current position in this output stream.
	 */
	void mark() override;

	/**
	 * Tests if this output stream supports the mark and reset methods.
	 *
	 * @return true if mark/reset is supported, false otherwise
	 */
	bool markSupported() override;

	/**
	 * Repositions this stream to the position at the time the mark method was
	 * last called on this output stream.
	 */
	void reset() override;
};

#endif// OZERO_IO_FILTER_OUTPUT_STREAM_H
