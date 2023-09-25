/**
 * Ozero IO
 *
 * A data input stream lets an application read data from a InputStream.
 */

#ifndef OZEROIO_IO_DATA_INPUT_STREAM_H
#define OZEROIO_IO_DATA_INPUT_STREAM_H 1

#include <DataInput/DataInput.h>
#include <FilterInputStream/FilterInputStream.h>
#include <InputStream/InputStream.h>

class DataInputStream : public virtual FilterInputStream, public virtual DataInput {
public:
	/**
	 * Public constructor.
	 *
	 * @param inputStream
	 */
	explicit DataInputStream(InputStream *inputStream);

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
};

#endif// OZEROIO_IO_DATA_INPUT_STREAM_H
