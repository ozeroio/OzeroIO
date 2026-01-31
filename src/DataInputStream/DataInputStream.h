/**
 * Ozero IO
 *
 * A data input stream lets an application read data from a InputStream.
 */

#ifndef OZERO_IO_DATA_INPUT_STREAM_H
#define OZERO_IO_DATA_INPUT_STREAM_H 1

#include <DataInput/DataInput.h>
#include <FilterInputStream/FilterInputStream.h>
#include <InputStream/InputStream.h>

class DataInputStream : public virtual FilterInputStream, public virtual DataInput {
public:
	/**
	 * Public constructor.
	 *
	 * @param inputStream The underlying input stream
	 */
	explicit DataInputStream(InputStream *inputStream);

	/**
	 * Reads the next unsigned char of data from the input stream.
	 *
	 * @return The next unsigned char of data, or -1 if end of stream is reached
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
};

#endif// OZERO_IO_DATA_INPUT_STREAM_H
