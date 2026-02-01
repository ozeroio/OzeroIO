/**
 * Ozero IO
 *
 * An output stream that also maintains a checksum of the data being written.
 * The checksum can then be used to verify the integrity of the output data.
 */

#ifndef OZERO_IO_CHECKED_OUTPUT_STREAM_H
#define OZERO_IO_CHECKED_OUTPUT_STREAM_H 1

#include <Checksum/Checksum.h>
#include <FilterOutputStream/FilterOutputStream.h>

class CheckedOutputStream : public FilterOutputStream {
protected:
	/**
	 * The Checksum to be applied to this stream.
	 */
	Checksum *checksum;

public:
	/**
	 * Creates an output stream using the specified Checksum.
	 *
	 * @param outputStream the output stream
	 * @param checksum the Checksum
	 */
	CheckedOutputStream(OutputStream *outputStream, Checksum *checksum);


	/**
	 * Returns the Checksum for this output stream.
	 *
	 * @return the Checksum value
	 */
	Checksum *getChecksum();

	/**
	 * Writes the specified <code>uint8_t</code> to this output stream.
	 * <p>
	 * The <code>write</code> method of <code>FilterOutputStream</code>
	 * calls the <code>write</code> method of its underlying output stream,
	 * that is, it performs <tt>outputStream->write(b)</tt>.
	 * <p>
	 * Implements the abstract <tt>write</tt> method of <tt>OutputStream</tt>.
	 *
	 * @param      b   the <code>unsigned char</code>.
	 */
	virtual void write(unsigned char b) override;

	/**
	 * Writes <code>len</code> bytes to this output stream.
	 * <p>
	 * The <code>write</code> method of <code>FilterOutputStream</code>
	 * calls its <code>write</code> method of two arguments with the
	 * arguments <code>b</code> and
	 * <codelen</code>.
	 *
	 * @param      b the data to be written.
	 * @param      len the length
	 */
	virtual void write(unsigned char *b, int len) override;

	/**
	 * Writes <code>len</code> bytes from the specified
	 * <code>unsigned char</code> array starting at offset <code>off</code> to
	 * this output stream.
	 *
	 * @param      b   the data.
	 * @param      off   the start offset in the data.
	 * @param      len   the number of bytes to write.
	 */
	virtual void write(unsigned char *b, int off, int len) override;
};

#endif /* OZERO_IO_CHECKED_OUTPUT_STREAM_H */
