/**
 * Ozero IO
 *
 * DataInputStream
 *
 * A data input stream lets an application read data from a InputStream.
 */

#ifndef OZEROIO_IO_DATA_INPUT_STREAM_H
#define OZEROIO_IO_DATA_INPUT_STREAM_H 1

#include <DataInput/DataInput.h>
#include <InputStream/InputStream.h>

class DataInputStream : public DataInput {

	/**
	 * The used input stream.
	 */
	InputStream *inputStream;

public:
	/**
	 * Public constructor.
	 *
	 * @param inputStream
	 */
	explicit DataInputStream(InputStream *inputStream);

	/**
	 * Reads a unsigned char from the stream.
	 *
	 * @return unsigned char
	 */
	unsigned char readByte() override;

	/**
	 * Reads a bool from the stream.
	 *
	 * @return bool
	 */
	bool readBoolean() override;

	/**
	 * Reads a char from the stream.
	 *
	 * @return char
	 */
	char readChar() override;

	/**
	 * Reads an unsigned char from the stream.
	 *
	 * @return unsigned char
	 */
	unsigned char readUnsignedChar() override;

	/**
	 * Reads a short from the stream.
	 *
	 * @return short
	 */
	short readShort() override;

	/**
	 * Reads an unsigned short from the stream.
	 *
	 * @return unsigned short
	 */
	unsigned short readUnsignedShort() override;

	/**
	 * Reads an int from the stream.
	 *
	 * @return int
	 */
	int readInt() override;

	/**
	 * Reads an unsigned int from the stream.
	 *
	 * @return unsigned int
	 */
	unsigned int readUnsignedInt() override;

	/**
	 * Reads a long from the stream.
	 *
	 * @return long
	 */
	long readLong() override;

	/**
	 * Reads a unsigned long from the stream.
	 *
	 * @return unsigned long
	 */
	unsigned long readUnsignedLong() override;

	/**
	 * Reads a float from the stream.
	 *
	 * @return float
	 */
	float readFloat() override;

	/**
	 * Reads a double from the stream.
	 *
	 * @return double
	 */
	double readDouble() override;

	/**
	 * Reads a array of bytes from the stream.
	 *
	 * @param b
	 * @param len
	 */
	void readFully(unsigned char *b, int len) override;

	/**
	 * Skips n bytes of the stream.
	 *
	 * @param n
	 * @return unsigned int The number of skipped bytes.
	 */
	unsigned int skipBytes(unsigned int n) override;
};

#endif// OZEROIO_IO_DATA_INPUT_STREAM_H
