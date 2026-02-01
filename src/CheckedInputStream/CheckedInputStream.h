/**
 * Ozero IO
 *
 * An input stream that also maintains a checksum of the data being read.
 * The checksum can then be used to verify the integrity of the input data.
 */

#ifndef OZERO_IO_CHECKED_INPUT_STREAM_H
#define OZERO_IO_CHECKED_INPUT_STREAM_H 1

#include <Checksum/Checksum.h>
#include <FilterInputStream/FilterInputStream.h>

class CheckedInputStream : public FilterInputStream {
protected:
	/**
	 * The Checksum to be applied to this stream.
	 */
	Checksum *checksum;

public:
	/**
	 * Creates an input stream using the specified Checksum.
	 *
	 * @param in the input stream
	 * @param checksum the Checksum
	 */
	CheckedInputStream(InputStream *inputStream, Checksum *checksum);


	/**
	 * Returns the Checksum for this input stream.
	 *
	 * @return the Checksum value
	 */
	Checksum *getChecksum();


	/**
	 * Reads a byte.
	 *
	 * @return the byte read, or -1 if the end of the stream is reached.
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
	 * Reads into an array of bytes. If {@code len} is not zero.
	 *
	 * @param b   the buffer into which the data is read
	 * @param off the start offset in the destination array {@code b}
	 * @param len the maximum number of bytes read
	 * @return    the actual number of bytes read, or -1 if the end
	 *            of the stream is reached.
	 */
	int read(unsigned char *b, int off, int len) override;
};

#endif /* OZERO_IO_CHECKED_INPUT_STREAM_H */
